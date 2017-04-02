#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <fcntl.h>

#define MY_SOCK_PATH "/tmp/socket"
#define LISTEN_BACKLOG 50

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define MAX_BUF 1024


int main(int argc, char *argv[]) {
	int sfd, cfd;
	char buf[MAX_BUF];
	struct sockaddr_un my_addr, peer_addr;
	socklen_t peer_addr_size;

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sfd == -1) handle_error("socket");
	
	memset(&my_addr, 0, sizeof(struct sockaddr_un));

	my_addr.sun_family = AF_UNIX;

	strncpy(my_addr.sun_path, MY_SOCK_PATH,
		sizeof(my_addr.sun_path) - 1);

	if(bind(sfd, (struct sockaddr *) &my_addr,
		sizeof(struct sockaddr_un)) == -1)
		handle_error("bind");
	
	
	if (listen(sfd, LISTEN_BACKLOG) == -1)
		handle_error("listen");

	peer_addr_size = sizeof(struct sockaddr_un);
	cfd = accept(sfd, (struct sockaddr *) &peer_addr,
		&peer_addr_size);
	if (cfd == -1)
		handle_error("accept");
	read(cfd, buf, MAX_BUF);
	write(cfd, "Hello", sizeof("Hello"));
	close(cfd);
	close(sfd);
	
	unlink(MY_SOCK_PATH);

	return 0;
}


