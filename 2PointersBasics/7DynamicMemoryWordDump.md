#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Originally to allocate memory you have to define the array to contain the maximum number of elements
you have to set a finite number of memory. it doesnt adjust or dynamically change when you need it

for example if you have 
```c
int dataArray [1000]; 
```

that can only store 1000, if you suddenly need more memory, then you cant get it, and if you exceed 1000 you will come into an error and the program will break

with dynamic memory you can allocate more memory when you need to
with this, if you need more it will make more room, and you wont have a loooong array with a lot of unused memory spaces

provides a strong incentive to use pointers in code. so that you can allocate memory dynamically
its all about efficiency and not using that much memory

its only possible if you have a pointer, because you have a pointer and you know where the memory is located, 
it is easy to readjust the memory from there

## HEAP
dynamic memory allocation is on the heap. it allows for more change, like change the size of variable
memory on the heap is controlled by the programmer, you have to delete the memory and free it.
want to control how much memory is used and when other apps can use it
can make it MUCH MUCH faster

## STACK
stack is more limiting
function arguments and local variables
when you execute a function the local variables are put on the stack 
when the function ends the memory is freed. so you no longer need it

# MEMORY FUNCTIONS

## MALLOC
allocating the memory at run time needs stdlib.h
if there is no more space to be allocated malloc returns null. 
its best practice to check if the pointer is null before using the pointer

### EXAMPLE
it frees up 100 bytes of memory for something, then you cast that memory to a pointer
integers are 4 bytes each so 100 means that it can hold 25 ints but the size of an int it might be different each time
```c
int *pNumberBad = (int*)malloc(100); 
```

instead, when using malloc you should specify the type of data you want to store inside the pointer

using this sizeof removing the assumption that each int is 4 bytes
it checks the system to see the size of an int and then times' it so you can allocate the number of ints you want
this is much better than the one above as it ensures you have the correct number of ints

```c
// it uses (int*) to type cast malloc into a int pointer. malloc typically returns a void pointer otherwise

int *pNumber = (int*)malloc(25 * sizeof(int))

pNumber = NULL;
free(pNumber); //always call free when you call malloc()
```

## SIZEOF
gets the number of bytes used to store a data type, because the size of a data type may change from system to system

## MEMORY LEAKS
a memory leak occurs when you allocate the memory dynamically but you do not release it when it is no longer being used
when you no longer have the reference. when you are in a loop allocate memory, then when you are out of the loop you no longer use it?

## FREE
to free up memory you have aloocated dynamically, you must still have access to the addresses to the block of memory
its better to allocate a large chunk of memory than a lot of small chunks

whereever you create malloc you should free in the same one

## REALLOCATE
if the array reaches max size, then you can give it more memory

```c
//like in an array, its making something so that it can hold 15 characters inside the str
str = (char *) malloc (15 * sizeof(char));
// need to use string copy so that all the elements inside 
strcpy(str, "melky");

printf("String = %s, Address = %p\n", str, str);

// reallocating
str = (char *) realloc(str, 25 * sizeof(char));
// concatenates to the last part of the string
strcat(str, " melk");
printf("String = %s, Address %p\n", str, str);

// now that we are done using the string free up the memory it used
free(str);
```