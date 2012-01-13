#include "threadpool.h"
#include "socketqueue.h"
#include "httpparser.h"
#include "socketlayer"

// BEGIN : page specific data

static const int
NUM_THREADS = 10;

static pthread_t
pool        [NUM_THREADS];

static pthread_mutex_t
lock        = PTHREAD_MUTEX_INITALIZER;

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
        http_request_data * data = parse_request(message);
        
        // we have the message now just need to figure out what the fuck to do with it
        // TODO: figure out what the fuck to do with it
        // TODO: send a response to the client about what the fuck we did with it

        free(data);
        free(message);
    }

}

// BEGIN : public interface

void
threadpool_init(void)
{
    for(int idx = 0, pthread_t * pool_itor = pool;
        idx < NUM_THREADS;
        ++idx, ++pool_itor)
    {
        pthread_create(pool_itor, NULL, &thread_main, NULL);
    }
}

void
socket_has_been_queued(void)
{
    pthread_cond_signal(&condition);
}

