#ifndef _SERVER_LOGGER_
#define _SERVER_LOGGER_

int
log_message(char * ip_address,
            char * time_stamp, 
            char * method, 
            char * document_name, 
            char * server_status);

#endif
