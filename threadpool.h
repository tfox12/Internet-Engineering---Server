#ifndef _SERVER_THREADPOOL_
#define _SERVER_THREADPOOL_

void
threadpool_init(void);

void
socket_has_been_queued(void);

void
destroy_threadpool(void);

#endif
