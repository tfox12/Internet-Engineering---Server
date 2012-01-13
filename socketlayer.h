#ifndef _SERVER_SOCKETLAYER_
#define _SERVER_SOCKETLAYER_

int
create_listening_socket();

char *
read_from_socket(int sockfd);

#endif
