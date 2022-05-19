#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	//make fifo, path to the file you want to create, permission (this file can be read from or wrote to anybody), 
	// errno to make sure that the error being thrown isnt for the file already existing 
	if (mkfifo("myfifo1", 0777) == -1 ){
		if (errno != EEXIST){
			puts("could not create fifo file");
		}	
		return 1;
	} 

	// takes in filepath and file flag (why you want to open it) and returns a file descriptor, only 1 because it just needs the 1 file
	// if you make something both read and write it will not wait
	int fd = open("myfifo1", O_WRONLY);
	// if you open a fifo for writing, the the current process will hang/block/pause until another program comes along and opens the same fifo for reading.
	// until that happens, it will not continue once it does it will continue, reading a file can be used like cat myfifo1 in the terminal

	int num = '@';
	// it writes the character even if you have a number value 97
	if (write(fd, &num, sizeof(num))){
		puts("something went wrong with writing");
		return 2;
	}

	close(fd);
	
	return 0;
}