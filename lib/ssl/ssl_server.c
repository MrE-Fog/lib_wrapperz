#include "ssl_server.h"

SSL_CTX* init_server_CTX()  {
    const SSL_METHOD *ssl_method;
    SSL_CTX *ssl_ctx;

    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    ssl_method = TLSv1_2_server_method();
    ssl_ctx = SSL_CTX_new(ssl_method);

    if (!ssl_ctx)   {
        // Server CTX creation failed
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ssl_ctx;
}

void destroy_server_CTX(SSL_CTX *ssl_ctx)   {
    if (ssl_ctx)    free(ssl_ctx);
}

void load_certs(SSL_CTX *ssl_ctx, const char *cert_file, const char *key_file)  {
    int failed=0;

    if (SSL_CTX_use_certificate_file(ssl_ctx, cert_file, SSL_FILETYPE_PEM) <= 0)    {
        ERR_print_errors_fp(stderr);
        failed = 1;
    }
    if (SSL_CTX_use_PrivateKey_file(ssl_ctx, key_file, SSL_FILETYPE_PEM) <= 0)  {
        ERR_print_errors_fp(stderr);
        failed = 1;
    }
    if (!SSL_CTX_check_private_key(ssl_ctx))    {
        // Private key and Public cert is not matching
        fprintf(stderr, "Private key doesn't match with Public cert");
        failed = 1;
    }
    
    if (failed) exit(EXIT_FAILURE);
}

void show_certs(const SSL *ssl)   {
    X509 *x509_cert;

    if (!(x509_cert=SSL_get_peer_certificate(ssl))) {
        char *line = NULL;

        printf("Server Certificate:\nIssuer name: %s\n", (line=X509_NAME_oneline(X509_get_issuer_name(x509_cert), 0, 0)));
        if (line)  free(line);
        X509_free(x509_cert);
    }
    else    {
        printf("No X509 certs found");
    }
}

int ssl_accept(SSL *ssl)    {
    if (SSL_accept(ssl) <= 0)   {
        ERR_print_errors_fp(stderr);
        return 1;
    }
    return 0;
}