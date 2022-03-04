#include <stdio.h>

int main(){
	int a, b, c;
	// because you are dereferencing it, you need to specify the data type of it. but you are storing the memory address itself 
	
	printf("Input the value of 1st element : ");
	scanf("%d", &a);
	printf("Input the value of 2nd element : ");
	scanf("%d", &b);
	printf("Input the value of 3rd element : ");
	scanf("%d", &c);
	
	// again need to point to the address of it
	int *pointerA = &a;
	int *pointerB = &b;
	int *pointerC = &c;

	printf("The value before swapping are: \n");
	printf("element 1 = %d\n", a);
	printf("element 2 = %d\n", b);
	printf("element 3 = %d\n", c);

	int temp = *pointerA;
	a = *pointerC;
	c = *pointerB;
	b = temp;z

	printf("\nThe value after swapping are: \n");
	printf("element 1 = %d\n", a);
	printf("element 2 = %d\n", b);
	printf("element 3 = %d\n", c);

	return 0;
}

void swapNumbers(int *x,int *y,int *z);
int main2()
{
    int e1,e2,e3;
	printf("\n\n Pointer : Swap elements using call by reference :\n"); 
	printf("------------------------------------------------------\n");	
    printf(" Input the value of 1st element : ");
    scanf("%d",&e1);
	printf(" Input the value of 2nd element : ");
    scanf("%d",&e2);
	printf(" Input the value of 3rd element : ");
    scanf("%d",&e3);
	
	
    printf("\n The value before swapping are :\n");
    printf(" element 1 = %d\n element 2 = %d\n element 3 = %d\n",e1,e2,e3);
    swapNumbers(&e1,&e2,&e3);
    printf("\n The value after swapping are :\n");
    printf(" element 1 = %d\n element 2 = %d\n element 3 = %d\n\n",e1,e2,e3);
    return 0;
}
void swapNumbers(int *x,int *y,int *z)
{
    int tmp;
    tmp=*y;
    *y=*x;
    *x=*z;
    *z=tmp;
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