# include <stdio.h>

int main(){
    //array of 100 ints
	# include <stdio.h>

	/*
	integer array that holds 100 integers
	an array is a pointer essentially just the first element in memory, 
	and the rest of the numbers are stored sequentially next to each other
    */
	
	int values[100];
    int *valuesPtr; //have to use malloc lol

    // when you call the variable name for the array, it just gives the pointer to the first element in the values array 
    // so when making a pointer go to an array you dont need to use the & to get the memory address 
    valuesPtr = values; 
    //it would be the same thing as getting the address of the first element in the array
    valuesPtr = &values[0]

    i = 0;
    //these are the same thing
    value[i]
    *(valuesPtr + i)
    valuesPtr++ //only works with pointers

    //increments the pointer to 3 ahead, the 4th element. and dereferences. so it grabs the value at valuesPtr[3]
    *(valuesPtr + 3);

    //to set values inside you can increment by which index you want and dereference it valuesPt
    *(valuesPtr + 10) = 27;

	// FIXME note this will not work, the following comments are to explain why this would not work
	char x[10]; // the specific area of memory is reserved to be size 10. char x[10] is constant information that has to be persistant within the entirety of the program
	x = "hello" // by assigning x as "hello" its essentially trying to reassign the value of x, but x should already be constant 
	// this will most likely result in a seg fault 

	// if you were to print a string array, it would keep printing everything until it hits a null byte
}