#ifndef _SERVER_SOCKETLAYER_
#define _SERVER_SOCKETLAYER_

int
create_listening_socket(void);

char *
read_from_socket(int sockfd);

void
write_to_socket(int sockfd, char * message, int message_length);

#endif
