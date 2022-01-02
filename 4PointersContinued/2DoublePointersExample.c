#include <stdio.h>

int main(){
	int a = 10;

	int *p1 = NULL;
	int **p2 = NULL;

	p1 = &a; //makes the pointer to a's address 
	p2 = &p1; //makes the pointer to the pointer's address

	printf("Address of a = %p\n", &a);
	printf("Address of p1 = %p\n", &p1);
	printf("Address of p2 = %p\n\n", &p2);

	return 0;
}