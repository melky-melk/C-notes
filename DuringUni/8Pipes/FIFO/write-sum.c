#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char* argv[]) {
	// create random array of 5 numbers
	int arr[5];
	srand(time(NULL));
	for (int i = 0; i < 5; i++){
		arr[i] = rand() % 100;
		printf("Generated %d\n", arr[i]);
	}

	int fd = open("sum", O_WRONLY);
	if (fd == -1){
		puts("something went wrong with opening the sum fifo file");
		return 1;
	}

	// if you got here that means you have already read it from another process
	// instead of using a for loop you can write the entire loop at once
	if (write(fd, arr, sizeof(int) * 5) == -1){
		puts("could not write");
		return 2;
	}

	close(fd);

	return 0;
}