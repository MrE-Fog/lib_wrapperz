#include "lib/ssl/ssl_server.h"
#include "lib/ssl/ssl_common.h"
#include "lib/socket/socket_server.h"
#include <stdio.h>

void server_lifecycle(int port)	{
	const char *msg = "Hello socket world!";
	SSL_CTX* ssl_ctx = init_server_CTX();
	load_certs(ssl_ctx, "cert/server_socket.pem", "cert/server_socket.pem");
	int server_sock_d = init_sock_conn(port, 1);
	int client_d = accept_sock_conn(server_sock_d);
	
	SSL* ssl = init_ssl(ssl_ctx);
	ssl_set_fd(ssl, client_d);

	if (!ssl_accept(ssl))	exit(EXIT_FAILURE);
	
	show_certs(ssl);
	
	if (ssl_write(ssl, (void *) msg, strlen(msg)))	{
		printf("Message sent to client");
	}
	
	destroy_sock_conn(client_d);
	destroy_sock_conn(server_sock_d);
	destroy_ssl(ssl);
	destroy_server_CTX(ssl_ctx);
	sleep(1);
}

int main(int argc, char **argv)	{
	if (argc != 2)	exit(EXIT_FAILURE);
	while(1)	{
		server_lifecycle(atoi(argv[1]));
	}
}