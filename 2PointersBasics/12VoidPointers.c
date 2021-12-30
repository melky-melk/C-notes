# include <stdio.h>

int main(){
    int i = 10;
    float f = 2.34;
    char ch = 'k';

    // its a pointer that can be used for multiple types of data types because it points to nothing, however when you want to use it it has to be referenced
    void *voidPointer;

    voidPointer = &i;
    // need to put the int 
    printf("Value of i = %d\n", *(int *)voidPointer)

    voidPointer = &f;
    printf("Value of i = %f\n", *(float *)voidPointer)
    
    voidPointer = &ch;
    printf("Value of i = %c\n", *(char *)voidPointer)
}