#include "threadpool.h"
#include "socketqueue.h"
#include "socketlayer.h"
#include "httpparser.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __unix__

#include <pthread.h>
#include <sys/socket.h>

typedef pthread_t           thread;
typedef pthread_mutex_t     mutex;
typedef pthread_cond_t      condition_variable;

#elif defined _WIN32

#include <Windows.h>
#include <WinSock.h>

typedef HANDLE              thread;
typedef CRITICAL_SECTION    mutex;
typedef CONDITION_VARIABLE  condition_variable;

#endif

// BEGIN : page specific data

#define NUM_THREADS 10

static thread
pool[NUM_THREADS];

static mutex
#ifdef __unix__
lock        = PTHREAD_MUTEX_INITIALIZER;
#elif defined _WIN32
lock;
#endif

static condition_variable
#ifdef __unix__
condition   = PTHREAD_COND_INITIALIZER;
#elif defined _WIN32
condition;
#endif

#ifdef __unix__
static int (* lock_mutex)(mutex *) = pthread_mutex_lock;
#elif defined _WIN32
static void (__stdcall* lock_mutex)(mutex *) = EnterCriticalSection;
#endif

#ifdef __unix__
static int (* unlock_mutex)(mutex *) = pthread_mutex_unlock;
#elif defined _WIN32
static void (__stdcall* unlock_mutex)(mutex *) = LeaveCriticalSection;
#endif

/*because there is a parameter difference,
  we need to make this an actual call and not an alias*/
static void
wait_on_condition(condition_variable * cnd, mutex * mtx)
{
#ifdef __unix__
    pthread_cond_wait(cnd,mtx);
#elif defined _WIN32
    SleepConditionVariableCS(cnd,mtx,INFINITE);
#endif
}

#ifdef __unix__
static int (* wake_a_sleeper)(condition_variable *) = pthread_cond_signal;
#elif defined _WIN32
static void (__stdcall* wake_a_sleeper)(condition_variable *) = WakeConditionVariable;
#endif

static
#ifdef __unix__
void *
thread_main(void * thread_arg)
#elif defined _WIN32
DWORD
thread_main(LPVOID thread_arg)
#endif
{
    for(;;)
    {
        int sockfd;
        char * message;
        char response[] = "poop";

        lock_mutex(&lock);
        sockfd = dequeue_socket();
        if(sockfd == QUEUE_EMPTY)
        {
            wait_on_condition(&condition,&lock);
            unlock_mutex(&lock);
            continue;
        }
        unlock_mutex(&lock);

        // as of this point we have acquired a socket file descriptor        

        message = read_from_socket(sockfd);
     
        printf("%s\n",message);
        
        write_to_socket(sockfd,response,4);

        printf(":D\n");

        free(message);
        close_socket(sockfd);
    }

}

// BEGIN : public interface

void
threadpool_init(void)
{
    int idx;
    for(idx = 0; idx < NUM_THREADS; ++idx)
    {
#ifdef __unix__
        pthread_create(pool+idx, NULL, &thread_main, NULL);
#elif defined _WIN32
        pool[idx] = CreateThread(
                        NULL, 0,
                        (LPTHREAD_START_ROUTINE)&thread_main,
                        NULL, 0, 0);
#endif
    }
}

void
socket_has_been_queued(void)
{
    wake_a_sleeper(&condition);
}

