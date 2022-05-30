#include <stdio.h>

void swap (int a[], int b[]);

int main(){
	int a = 2;
	int b = 3;

	printf("before swap a = %d b = %d\n", a,b);
	swap(&a, &b); //Specify the variables to swap and pass in the addresses
	printf("after swap: a = %d b = %d\n", a, b); // should print 3 2
	return 0;
}

//int a[], int b[] will still work
void swap (int *a, int *b){
	// get the value for a and save it in a new variables
	int temp = *a;

	// change what the a pointer points to, it now points to what the value of b is 
	*a = *b;
	// now make the b point go back to what a was;
	*b = temp;
}


// void swap (int *a, int *b){
// 	int * temp = *a;

// 	*a = *b
// 	*b = *temp;
// }
