#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

int main()
{
	int *ptr = NULL;
	ptr = (int *) malloc (sizeof (int));
	*ptr = 10;

	//when given it, it is given the address of a, but that doesnt change the value of ptr 
	// because inside of a function it isnt changed because a function isnt global
	foo(ptr);
	// the address of ptr is just a pointer
	fooDoublePointer(&ptr);
}

void foo(int *ptr){
	int a = 5;
	ptr = &a; //to make it work *ptr = a;
}

void fooDoublePointer(int **ptr){
	int a = 5;
	*ptr = &a;
}