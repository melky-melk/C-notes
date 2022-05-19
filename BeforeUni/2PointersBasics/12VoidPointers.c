# include <stdio.h>

int main(int argc, char **argv){
    int i = 10;
    float f = 2.34;
    char ch = 'k';

    // its a pointer that can be used for multiple types of data types because it points to nothing, 
	// however when you want to use it it has to be referenced
	// you can assign any pointer to it, as long as you type case it it will work
    void *voidPointer;

    voidPointer = &i;
    // need to put the int 
    printf("Value of i = %d\n", *(int *)voidPointer)

    voidPointer = &f;
    printf("Value of i = %f\n", *(float *)voidPointer)
    
    voidPointer = &ch;
    printf("Value of i = %c\n", *(char *)voidPointer)

	// this is valid it is used if we dont know the final type
	void **vp = (void **) argv;
}