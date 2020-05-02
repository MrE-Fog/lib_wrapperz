#include "socket_server.h"

int init_sock_conn(uint16_t port, int total_connections)   {
	int socket_d;
	struct sockaddr_in address;

	socket_d = socket(AF_INET, SOCK_STREAM, 0);

	memset((void *) &address, 0, sizeof(address));
	
	address = (struct sockaddr_in) {
		.sin_family = AF_INET,
		.sin_port = htons(port),
		.sin_addr.s_addr = INADDR_ANY
	};

	if (bind(socket_d, (const struct sockaddr *) &address, sizeof(address)) != 0)	{
		//	Can't bind port
		exit(EXIT_FAILURE);
	}

	if (listen(socket_d, total_connections) != 0)	{
		// Can't listen
		exit(EXIT_FAILURE);
	}

	return socket_d;
}

int accept_sock_conn(int socket_d)	{
	struct sockaddr client_addr;
	socklen_t client_addr_len = (socklen_t) sizeof(client_addr);

	return accept(socket_d, &client_addr, &client_addr_len);
}

void destroy_sock_conn(int socket_d)	{
	close(socket_d);
}