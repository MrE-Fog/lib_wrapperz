#ifndef _CHATAPP_SOCKET_COMMON_H_
#define _CHATAPP_SOCKET_COMMON_H_

#include <openssl/err.h>
#include <openssl/ssl.h>

SSL* init_ssl(SSL_CTX *ssl_ctx);
void destroy_ssl(SSL *ssl);
int ssl_read(SSL *ssl, void *buffer, size_t buffer_size);
int ssl_write(SSL *ssl, const void * buffer, size_t buffer_size);
int ssl_r_w(int mode, SSL *ssl, void *buffer, size_t buffer_size);
int ssl_set_fd(SSL* ssl, int fd);
int ssl_get_fd(SSL* ssl);

#endif