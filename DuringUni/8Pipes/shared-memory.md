mmap() is the function that 

the actual ram is the visible memory, and the addresses are not actual addresses in the physical memory. if you run multiple programs and print addresses you will get similar addresses

those are actually virtual addresses because your operating system gives a huge bunch of addresses o use. you have momory to yourself but it doesn. these addresses arent actually backed by physical memory. but when you dereference them you get the actual physical memory

mmap, gets some of the virtual addresses and makes them point to something, like a file you need. instead of having to read from it and write from places, you just get the pointer themselves

it gets memory from places? 

maps file or disk from memory to be able to change. get a reigon of memory and use it like malloc? its like lower level

get a region of memory to use that you need to share with other processes

mallocing memory and giving other processes access to it. 

can ask the kernal to give memory addresses near a certain address like somewhere around it? 

you usually give it null because it doesnt really matter, len length, prot is the permissions you want for the memory, if flags is not anon, you need to give it a file descriptor, and and offset

can read all of the parameters needed. the way you can tell a map what you want it to do

name of the file you want to map in. 


```c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#define SOME_DATA (24)
int main(int argc, char** argv) {
	if(argc != 2) {
		//Need two arguments
		return 1;
	}

	char* block = NULL;
	int fd = open(argv[1], O_RDONLY);
	struct stat stat_b;
	fstat(fd, &stat_b);
	block = mmap(NULL, stat_b.st_size, PROT_WRITE|PROT_READ,
	MAP_PRIVATE, fd, 0);
	
	if(block == MAP_FAILED) {
		perror("MMAP Failed");
		close(fd);
		return 1;
	}
	//Read some bytes
	for(size_t i = 0; i < SOME_DATA, i++) {
		printf("%c", block[i]);
	}
	printf("\n");
	munmap(block, stat_b.st_size);
	close(fd);
}
```

can use it like a character array you have malloced youself.

with map anon, you give a file descriptor of -1

when you mmap memory vefore the fork, only 1 mmap is made. when you do map_shared it would both point to the same thing. if you change the shared map address in another thing, it would change the shared map address in the place where it was created

mmap is basically like a shared array when you give it the private map thingo when you fork and give things to a child

map_private | map_anon is basically anon, but its not in the heap. its in some random piece of memory. its physical memory

STACK AND HEAP ARE ONLY IN VRAM

THEY ARE SEQUENTIAL IN VRAM BUT NOT IN ACTUAL MEMORY

VRAM BASICALLY ORGANISES EVERYTHING FOR 

its basically using vram to guve a specifica address

`shm_open` is the same thing as opening files. like in mkfifo, you can access things from not just the child and parent, you can do it from other programs

can cat the mapped memory