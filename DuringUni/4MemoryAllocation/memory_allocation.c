# include <stdio.h>

int main(){
	//pointer
	int * ptr;
	//malloc returns a void pointer because it doesnt know what you want to keep in there
	ptr = (int *)malloc(sizeof(int)*20); //allocates a chunk of memory in the heap, and returns a pointer to the first byte in the contiguous memory

	free(ptr) //gets rid of the bytes its storying, deallocates memory
	//calloc is similar to maloc, except it takes in the number of elements and the size of each element. 
	ptr = (int *) calloc(20, sizeof(int));

	free(ptr) //gets rid of the bytes its storying, deallocates memory
}