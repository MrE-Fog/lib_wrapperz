#ifndef _CHATAPP_SOCKET_SERVER_H_
#define _CHATAPP_SOCKET_SERVER_H_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/*
	Takes Host Name, Port and Total Connection/s
	-> Port no should be b/w 1-65535 (1-1024) requires root access
	-> Total Connection is for how many connection to handle (Should be set to 5 max)
*/
int init_sock_conn(uint16_t port, int total_connections);

/*
    Used to close socket connection and free up all resources
*/
void destroy_sock_conn(int socket_d);

/*
    Program waits on this call until any client joins
    returns new socket descriptor to talk to that client
	takes server socket descriptor as argument
*/
int accept_sock_conn(int socket_d);

#endif