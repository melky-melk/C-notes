#include <stdio.h>

/*
passing by value is when a function copies the arguement given in the parameters
and then changes those values inside so it can be used in its own variables (not global).
e.g. in a sum function if you give it a and b the a is not the same a as before it isnt changed
the changes made to the values given inside of the parameters are only within the function

passing by reference is when a value given to the function is the actual value outside of the function
meaning you can choose to make that value global. the changes made to the variable inside the function are also carried out outside
*/

void swapUsingPointers(int *x, int *y);
void swapWithoutPointers(int x, int y);
// so you cant change the pointer to x
void squareNumber(int const *x);

int main(){
    int a = 100;
    int b = 200;

    printf("Value of a is :%d\n", a);
    printf("Value of b is :%d\n", b);


    swapWithoutPointers(a,b);
    printf("\nNow swapping without pointers\n");
    printf("Value of a is :%d\n", a);
    printf("Value of b is :%d\n", b);

    swapUsingPointers(&a, &b);
    printf("\nNow swapping with pointers\n");
    printf("Value of a is :%d\n", a);
    printf("Value of b is :%d\n", b);

    int number = 5;

    printf("Number : %d\n", number);
    squareNumber(&number);
    printf("Number squared : %d\n", number);

    return 0;
}

void squareNumber(int const *x){
    // the new value of x is the value of x times by the value of x
    *x *= *x;
    return;
}

void swapUsingPointers(int *x, int *y){
    int temp;

    temp = *x;
    *x = *y;
    *y = temp;

    return;
}

void swapWithoutPointers(int x, int y){
    int temp;

    temp = x;
    x = y;
    y = x;

    return;
}