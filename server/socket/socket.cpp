#include "socket.hpp"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h> // sockaddr_in6
#include <unistd.h> // close
#include <stdio.h> // perror

static struct sockaddr_in6 getAddr(unsigned int port);
static int startSocket(unsigned int port);

int initSocket(unsigned int port) {
	int fd = startSocket(port);
	switch (fd) {
		case -1:
			perror("socket error");
			return -1;
		case -2:
			perror("bind error");
			return -2;
		case -3:
			perror("listen error");
			return -3;
	}

	return fd;
}

static int startSocket(unsigned int port) {
	int fd = socket(AF_INET6, SOCK_STREAM, 0);
	if (!fd)
		return -1;

	int opt = 1; // enable reuse of address
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
	struct sockaddr_in6 addr6 = getAddr(port);

	if (!bind(fd, (struct sockaddr*)&addr6, sizeof(addr6))) {
		close(fd); // close socket
		return -2;
	}
	
	// 4096 defines the maximum length to which the queue of pending connections for sockfd (var fd) may grow (default value for most systems)
	if (!listen(fd, 4096)) {
		close(fd); // close socket
		return -3;
	}

	return fd;
}

static struct sockaddr_in6 getAddr(unsigned int port) {
	struct sockaddr_in6 addr6;
	addr6.sin6_family = AF_INET6;
	addr6.sin6_port = htons(port);
	addr6.sin6_flowinfo = 0;
	addr6.sin6_addr = in6addr_any;
	addr6.sin6_scope_id = 0;
	
	return addr6;
}