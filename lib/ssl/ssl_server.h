#ifndef _SSL_CHATAPP_SSL_SERVER_
#define _SSL_CHATAPP_SSL_SERVER_

#include <openssl/ssl.h>
#include <openssl/err.h>

SSL_CTX* init_server_CTX();
void destroy_server_CTX(SSL_CTX *ssl_ctx);
void load_certs(SSL_CTX *ssl_ctx, const char *cert_file, const char *key_file);
void show_certs(const SSL *ssl);
int ssl_accept(SSL *ssl);

#endif