#include <stdio.h>
#include <stdlib.h>

// declare the function
int stringLength(const char * string);

int main(){
    // automatically get a null terminator at the end of the list if you dont specify the size of the character array
    printf("%d \n", stringLength("Hello, world!"));
    printf("%d \n", stringLength("Chiara"));
    printf("%d \n", stringLength(""));
    printf("%d \n", stringLength("melk"));

    return 0;
}

int stringLength(const char * firstAddress){
    // make another pointer that is the string 
    const char *lastAddress = firstAddress; 
    
    // if you dereference a null terminator, the answer will be 0 so to check if it is at the end of the array just do this
    // while *lastAddress != '/0'
    while (*lastAddress){
        // increment the position of the pointer which will be an integer
        ++lastAddress;
    }

    // the lastAddress minused by the starting position of the array will equal the length of the array 
	// remember that pointers are just numbers
    return lastAddress - firstAddress;
}