CC = gcc
STD = -std=c11
WARN = -Wall
OPTIMIZE = -00
LINKS = -L/usr/lib
SSL_LIBS = -lssl -crypto
THREAD_LIBS = -lpthread

all : chatapp_server chatapp_client

chatapp_server : chatapp_server.c
	$(CC) $(STD) $(WARN) $^ -o $@ $(LINKS)

chatapp_server : chatapp_client.c
	$(CC) $(STD) $(WARN) $^ -o $@ $(LINKS)

thread_lib_check : thread_lib_check.c lib/thread/thread_pool.c
	$(CC) $(STD) $(WARN) $^ -o $@ $(THREAD_LIBS)

clean :
	rm chatapp_client chatapp_server thread_lib_check *.o