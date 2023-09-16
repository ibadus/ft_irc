#include "socket.hpp"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h> // sockaddr_in
#include <unistd.h> // close
#include <stdio.h> // perror

static struct sockaddr_in getAddress(unsigned int port);
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

unsigned int getPort(int fd) {
	struct sockaddr_in address;
	socklen_t len = sizeof(address);
	getsockname(fd, (struct sockaddr*)&address, &len);
	return ntohs(address.sin_port);
}


static int startSocket(unsigned int port) {
	int fd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP
	if (fd < 0)
		return -1;

	int opt = 1; // enable reuse of address
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	struct sockaddr_in address = getAddress(port);

	if (bind(fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		close(fd); // close socket
		return -2;
	}

	// 4096 defines the maximum length to which the queue of pending connections for sockfd (var fd) may grow (default value for most systems)
	if (listen(fd, 4096) < 0) {
		close(fd); // close socket
		return -3;
	}

	return fd;
}

static struct sockaddr_in getAddress(unsigned int port) {
	struct sockaddr_in addr;
	addr.sin_family = AF_INET; // IPv4
	addr.sin_addr.s_addr = INADDR_ANY; // listen on all interfaces
	addr.sin_port = htons(port); // convert to network byte order
	
	return addr;
}