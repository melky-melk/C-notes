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

	int fd = open("sum", O_RDONLY);
	if (fd == -1){
		puts("something went wrong with opening the sum fifo file for reading");
		return 1;
	}

	// if you got here that means you have already read it from another process
	// can do instead of a for loop
	// read(fd, arr, sizeof(int) * 5);
	
	for (int i = 0; i < 5; i++){
		if (read(fd, &arr[i], sizeof(int)) == -1){
			puts("could not read");
			return 2;
		}

		printf("Recieved %d\n", arr[i]);
	}

	close(fd);

	int sum = 0;

	for (int i = 0; i < 5; i++){
		sum += arr[i];
	}

	printf("Result is %d\n", sum);

	return 0;
}