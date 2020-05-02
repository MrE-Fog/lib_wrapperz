#include "socket_client.h"

/*
    Open socket connection to connect to host takes 2 args
    Host Name of the server (localhost or the string identified hostname)
    Port to connect to (1-65535)
*/
int open_sock_conn(const char* host_name, uint16_t port) {
    struct hostent *host;
    struct sockaddr_in address;

    if (!(host=gethostbyname(host_name)))   {
        // Hostname not resolved to address
        exit(EXIT_FAILURE);
    }

    int socket_d = socket(AF_INET, SOCK_STREAM, 0);

    memset((void *) &address, 0, sizeof(address));

    address = (struct sockaddr_in)  {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = *(long *) (host->h_addr)
    };

    if (connect(socket_d, (const struct sockaddr *) &address, sizeof(address)) != 0)    {
        close(socket_d);

        // Failed to connect
        exit(EXIT_FAILURE);
    }

	return socket_d;
}

/*
    Resources free-up
*/
void destroy_sock_conn(int socket_d)    {
    close(socket_d);
}