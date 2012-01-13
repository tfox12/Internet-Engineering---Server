#include "threadpool.h"
#include "socketqueue.h"
#include "socketlayer.h"

// BEGIN : page specific data

#define NUM_THREADS 10

static pthread_t
pool[NUM_THREADS];

static pthread_mutex_t
lock        = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t
condition   = PTHREAD_COND_INITIALIZER;

static void *
thread_main(void * thread_arg)
{
    for(;;)
    {
        pthread_mutex_lock(&lock);
        int sockfd = dequeue_socket();
        if(sockfd == QUEUE_EMPTY)
        {
            pthread_cond_wait(&condition,&lock);
            pthread_mutex_unlock(&lock);
            continue;
        }
        pthread_mutex_unlock(&lock);

        // as of this point we have acquired a socket file descriptor        

        char * message = read_from_socket(sockfd);
     
        write_to_socket(sockfd,message,sizeof(message));

        free(message);
    }

}

// BEGIN : public interface

void
threadpool_init(void)
{
    int idx;
    for(idx = 0; idx < NUM_THREADS; ++idx)
    {
        pthread_create(&pool[idx], NULL, &thread_main, NULL);
    }
}

void
socket_has_been_queued(void)
{
    pthread_cond_signal(&condition);
}

