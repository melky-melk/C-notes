#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	// keys to the pipe, a pipe has 2 file descriptors because a pipe should have 2 "ends" they are stored in there
	int file_descriptor[2];
	// file_descriptor[0] should be the read file
	// file_descriptor[1] should be the write file
	//takes 2 integers, file descriptors to the pipe, they act as an key to say if you want to write or read to it, its like a file, but you have 2
	
	// pipe command creates the pipe
	if (pipe(file_descriptor) == -1) { 
		puts("an error occured with opening a pipe");
		return 1;
	}

	// now that you have a pipe you can fork
	// when the program forks the file descriptors remain intact, they get inherited by the child program
	// the file descriptors can be open or closed independantly of each other
	int fork_ret = fork();

	if (fork_ret == -1){
		puts("an error occured with forking");
		return 4;
	}
	
	// value is 0 that means it is the child process, (remember parent process' fork ret is the pid of the child)
	if (fork_ret == 0){
		// because the descriptors are inherited, you need to close the files you are not going to use
		close(file_descriptor[0]); 
	
		int num;
		printf("INPUT A NUMBER\n");
		scanf("%d", num);

		// //where to write, where to get the value ur writing, the size
		if (write(file_descriptor[1], &num, sizeof(int)) == -1) {
			puts("an error with writing to a file");
			return 2;
		}
		// after writing remember to close
		close(file_descriptor[1]); //tells anything that is reading the file that it is close, it cannot be used
	}
	// meaning it is a parent
	else {
		close(file_descriptor[1]);

		int num;
		//again, read the file INTO num so num is now what it is
		if (read(file_descriptor[0], &num, sizeof(int)) == -1){
			puts("an error with reading the file");
			return 2;
		} 
			
		close(file_descriptor[0]);

		printf("Got from child process %d\n", num);
	}
	
	return 0;
}