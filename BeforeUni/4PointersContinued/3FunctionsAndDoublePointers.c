#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void foo(char *ptr);
void fooDoublePointer(char **ptr);

int main()
{
	int *ptr = NULL;
	ptr = (int *) malloc (sizeof (int));
	*ptr = 10;
	
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
