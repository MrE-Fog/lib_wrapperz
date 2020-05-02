#ifndef _CHATAPP_SOCKET_CLIENT_H_
#define _CHATAPP_SOCKET_CLIENT_H_

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int open_sock_conn(const char* host_name, uint16_t port);
void destroy_sock_conn(int socket_d);

#endif