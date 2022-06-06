#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	int arr[] = { 1, 2, 3, 4, 1, 2 };
	int length = sizeof(arr) / sizeof(int);
	int start, end;
	int fd[2];
	if (pipe(fd) == -1){
		puts("could not create pipe");
		return 1;
	}

	int id = fork();
	if (id == -1){
		puts("fork fail");
		return 2;
	}

	if (id == 0){
		start = 0;
		end = length/2;
	}
	else {
		start = length/2;
		end = length;
	}

	int sum = 0;
	for (int i = start; i < end; i++){
		sum += arr[i];
	}

	printf("Calculated partical sum: %d\n", sum);

	// if it is the child process
	if (id == 0){
		close(fd[0]);
		// gives the sum value to the parent
		write(fd[1], &sum, sizeof(sum));
		close(fd[1]);
	}
	else {
		close(fd[1]);

		int child_sum;
		read(fd[0], &child_sum, sizeof(child_sum));
		close(fd[0]);

		printf("Total sum: %d\n", child_sum + sum);
		wait(NULL);
	}

	return 0;
}