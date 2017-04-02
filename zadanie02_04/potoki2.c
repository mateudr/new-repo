#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	int fd;
	char * myfifo = "/tmp/myfifo";

	/* create the FIFO (named pipe) */
	mkfifo(myfifo, 0666);

	/*write "Hi" to the FIFO */
	fd = open(myfifo, O_WRONLY);
	write(fd, "Hi", sizeof("Hi"));
	close(fd);

	/* remove the FIFO */
	unlink(myfifo);
	
	return 0;
}
