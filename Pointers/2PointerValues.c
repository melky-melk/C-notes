#include <stdio.h>

int main(){
    int value = 0;
    int *pvalue = &value;

    printf("Input an integer: ");
    // normally when you get input from a scanner you have to feed it an address in the parameters
    // like scanf("%d", &value), but because pointers are already values then you can straight up just feed it the pointer because the pointer is already just the memory address 
    scanf("%d", pvalue);

    // do not dereferencean initiallised pointer
    int * pointer;
    // *pointer = 5; //error it is trying to store 5 at a loction pt points to but pt hasnt stored anything
    // so you dont know where it is placed. it might be harmless, it might overwrite some code or it might cause the program to crash

    // to avoid this initialize all your pointers to null
    int *pvalue = NULL;
    int *pvalue = 0;

    if (*pvalue == NULL){}

    //if its not pointer then you can dereference it 
}