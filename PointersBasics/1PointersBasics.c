#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num = 150;
 
    // Give it nothing, but it has memory allocated to store
    // remember that the * dereferences it, so you are accessing the value its storing 
    int *pNum = NULL;

    // assign the address of num to pNum
    pNum = &num;
    
    printf("num address is : %p\n", &num); //prints the address to num
    printf("Value of pNum address: %p\n", &pNum); //prints its own address
    printf("Value of the pNum variable : %p\n", pNum); //prints the address to the num
    printf("Value of what pNum is pointing to : %d\n", *pNum); //goes to the adress its storing and gets the number

    return 0;
}