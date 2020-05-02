#include "socket_common.h"

inline int read_from_sock_d(int accepted_sock_d, void* buffer, size_t buffer_size)	{
	return read(accepted_sock_d, buffer, buffer_size);
}

inline int write_to_sock_d(int accepted_sock_d, const void* buffer, size_t buffer_size)	{
	return write(accepted_sock_d, buffer, buffer_size);
}

int r_w_sock_d(int mode, int accepted_sock_d, void* buffer, size_t buffer_size)	{
	return mode? write_to_sock_d(accepted_sock_d, (const void *) buffer, buffer_size) : read_from_sock_d(accepted_sock_d, buffer, buffer_size);
}