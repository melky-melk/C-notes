#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // 3 ways to declare a string
    char name[6] = "Chiara";                // making a character array knowing the number of characters then assign it 
    char myName[] = "Chiara";                 // making a character array with the empty ones
    char* Name = "Chiara";                  // Read only memory. making a pointer to the first character "C" then moving that along

    printf("%s\n", name);
    printf("%s\n", myName);
    printf("%s\n", Name);

    printf("Number of bytes: %ld\n", sizeof(name));
    printf("Number of bytes: %ld\n", sizeof(myName));
    printf("Number of bytes: %ld\n", sizeof(Name));        // Size of a pointer is always 8 in 64 bit machine

    printf("%ld\n", strlen(name));
    printf("%ld\n", strlen(myName));
    printf("%ld\n", strlen(Name));

    name[2] = 'e';
    myName[2] = 'e';
    // Name[2] = 'e';     // Will cause Seg fault. Cannot modify read only memory

    printf("%c\n", *Name); //dereference the name to get the FIRST ELEMENT OF THE ARRAYLIST
    Name++; // to get to the next character you increment where the pointer is to access the h
    printf("%c\n", *Name); 
    Name++;
    printf("%c\n", *Name); 

	

    
}