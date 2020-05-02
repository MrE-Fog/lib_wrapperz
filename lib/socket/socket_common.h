#ifndef _CHATAPP_SOCKET_COMMON_H_
#define _CHATAPP_SOCKET_COMMON_H_

#include <unistd.h>

int read_from_sock_d(int accepted_sock_d, void* buffer, size_t buffer_size);
int write_to_sock_d(int accepted_sock_d, const void* buffer, size_t buffer_size);

/*
    Function to read and write to connected socket client
    -> if mode is 0 reading is done
    -> if mode is not 0 writing is done
*/
int r_w_sock_d(int mode, int accepted_sock_d, void* buffer, size_t buffer_size);

#endif