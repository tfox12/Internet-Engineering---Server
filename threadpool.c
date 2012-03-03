/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#include "threadpool.h"
#include "socketqueue.h"
#include "socketlayer.h"
#include "httpparser.h"
#include "httpget.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef __unix__

#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef pthread_t           thread;
typedef pthread_mutex_t     mutex;
typedef pthread_cond_t      condition_variable;

#elif defined _WIN32

#include <WinSock2.h>
#include <Windows.h>

typedef HANDLE              thread;
typedef CRITICAL_SECTION    mutex;
typedef CONDITION_VARIABLE  condition_variable;

#endif

// BEGIN : page specific data

#define NUM_THREADS 10

static thread
pool[NUM_THREADS];

/* below are various typedef's for cross platform
   capabilities. This also includes function pointers that
   map a facade to the appropriate platform's API. */

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

/**************************************************************************** 
FILE SPECIFIC SUB-ROUTINE

GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Chooses the correct handler according to the request
    data.
****************************************************************************/
static http_response_data *
handle_request(http_request_data * request)
{
    if(!strcmp(request->method,"GET"))
    {
        return handle_get(request);
    }
    else
        return NULL;
}

/**************************************************************************** 
FILE SPECIFIC SUB-ROUTINE

GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: This is the code that the threads in the pool run.
****************************************************************************/
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
        queue_node          * request_info;
        char                * message;
        char                * response_data;
        char                * response_itor;
        http_request_data   * request;
        http_response_data  * response;
        int                   response_length;
        char_node           * key_itor, 
                            * val_itor;
        int                   data_length;
        time_t                timestamp;

        lock_mutex(&lock);

        /* Get a socket */
        request_info = dequeue_socket();

        if(request_info == NULL)
        {
            wait_on_condition(&condition,&lock);
            unlock_mutex(&lock);
            continue;
        }
        unlock_mutex(&lock);    

        timestamp = time(NULL);

        printf("%s(%x):%i\r\n",inet_ntoa(request_info->client.sin_addr),
                               ntohl(request_info->client.sin_addr.s_addr),
                               ntohs(request_info->client.sin_port));
        
        /* read the data from the socket */
        message = read_from_socket(request_info->socket);
        if(!(*message)) continue;

        /* parse the data from the socket */
        request = parse_request(message);

        /* choose the correct handler and that handler will create
           response data */
        response = handle_request(request);

        /* turn response data into a response message */
        /* NOTE: this code should be moved into a "httpresponse" file */
        response_length = strlen(response->version) + 1 +
                          strlen(response->code)    + 1 +
                          strlen(response->phrase)  + /* I thought ahead, phra */
                          /*headers computed below*/+ 2;

        for(key_itor = response->headers_keys, val_itor = response->headers_values;
            key_itor && val_itor;
            key_itor = key_itor->next, val_itor = val_itor->next)
        {
            response_length += strlen(key_itor->val) + strlen(val_itor->val) + 4;
            if(!strcmp(key_itor->val,HEADER_CONTENT_LENGTH))
            {
                data_length = atoi(val_itor->val);
            }
        }
        response_length += data_length;

        response_data = response_itor = (char *) calloc(response_length,sizeof(char));

        memcpy(response_itor,response->version,strlen(response->version));
        *(response_itor += strlen(response->version)) = ' ';
        ++response_itor;

        memcpy(response_itor,response->code,strlen(response->code));
        *(response_itor += strlen(response->code)) = ' ';
        ++response_itor;

        memcpy(response_itor,response->phrase,strlen(response->phrase));
        response_itor += strlen(response->phrase);

        for(key_itor = response->headers_keys, val_itor = response->headers_values;
            key_itor && val_itor;
            key_itor = key_itor->next, val_itor = val_itor->next)
        {
            memcpy(response_itor,key_itor->val,strlen(key_itor->val));
            *(response_itor += strlen(key_itor->val)) = ':';
            *(++response_itor) = ' ';
            ++response_itor;

            memcpy(response_itor,val_itor->val,strlen(val_itor->val));
            *(response_itor += strlen(val_itor->val)) = '\r';
            *(++response_itor) = '\n';
            ++response_itor;
        }
        *(response_itor++) = '\r';
        *(response_itor++) = '\n';

        memcpy(response_itor,response->body,data_length);

        /* write our response string into the socket */
        write_to_socket(request_info->socket,response_data,response_length);


        /* log it */
        log_message(inet_ntoa(request_info->client.sin_addr),
                    ctime(&timestamp),
                    request->method,
                    request->uri,
                    response->code);

        /* clean up our mess */
        free(response_data);
        free_request_data(request);
        free_response_data(response);
        free(message);     
        close_socket(request_info->socket);
        free(request_info);
    }

}

// BEGIN : public interface
/**************************************************************************/
void
threadpool_init(void)
{
    int idx;
    for(idx = 0; idx < NUM_THREADS; ++idx)
    {
#ifdef __unix__
        pthread_create(pool+idx, NULL, &thread_main, NULL);
#elif defined _WIN32
        InitializeCriticalSection(&lock);
        pool[idx] = CreateThread(
                        NULL, 0,
                        (LPTHREAD_START_ROUTINE)&thread_main,
                        NULL, 0, 0);
#endif
    }
}

/**************************************************************************/
void
socket_has_been_queued(void)
{
    wake_a_sleeper(&condition);
}
