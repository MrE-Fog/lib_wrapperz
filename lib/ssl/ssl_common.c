#include "ssl_common.h"

SSL* init_ssl(SSL_CTX *ssl_ctx)	{
	return SSL_new(ssl_ctx);
}

void destroy_ssl(SSL *ssl)	{
	if (ssl)	SSL_free(ssl);
}

inline int ssl_read(SSL *ssl, void *buffer, size_t buffer_size)	{
	if (SSL_read(ssl, buffer, buffer_size) <= 0)	{
		ERR_print_errors_fp(stderr);
		return 0;
	}
	return 1;
}

inline int ssl_write(SSL *ssl, const void * buffer, size_t buffer_size)	{
	if (SSL_write(ssl, buffer, buffer_size) <= 0)	{
		ERR_print_errors_fp(stderr);
		return 0;
	}
	return 1;
}

int ssl_r_w(int mode, SSL *ssl, void *buffer, size_t buffer_size)	{
	return mode? ssl_write(ssl, (const void *) buffer, buffer_size) : ssl_read(ssl, buffer, buffer_size);
}

inline int ssl_set_fd(SSL* ssl, int fd)	{
	return SSL_set_fd(ssl, fd);
}

inline int ssl_get_fd(SSL* ssl)	{
	return SSL_get_fd(ssl);
}