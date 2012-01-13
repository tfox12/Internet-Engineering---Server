#ifndef _SERVER_THREADPOOL_
#define _SERVER_THREADPOOL_

#include <pthread.h>

void
threadpool_init(void);

void
socket_has_been_queued(void);

#endif
