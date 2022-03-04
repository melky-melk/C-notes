#include <stdio.h>
// to define static variables
#define BUFFER 1024
#define MAX 100

int main(){
    // there are no stings only character arrays, stores a bunch of characters inside a variable
    char realName[] = "Chiara";
    char onlineName[] = "melk";
    int age = 18;
    // how to do constant variables in C, you cannot now change the variable PI to be something else
    const double PI = 3.14;

    // i dont think you can do string concatenation...
    printf("Hello I am %s\n", realName);
    printf("I am also known as %s\n", onlineName);
    printf("I am %d years old\n", age );

	// when you create variables you reserve an area of memory if you initialise the variable
	int counter; //it tells the compiler, for this module, reserve a memory of this given size, automatically allocates

	/* 
	when you initialise the value you can fill in the bits of where the moemory is LOCATED
	in the initial initalisation there is no sensible value things are automatically assigned to. like int counter will not be 0
	int counter will be a completely random set of bits the compiler chooses where it points to
	and when you change the variable, you change the bits where the memory is located

	when you create an array
	*/

	// when this is executed, it will allocate, 100 x sizeof(int) bytes of memory
	// gives an initial memory address and 100 nonsense following values, they are layed out contingously next to each other
	int counters[MAX];

	char ch[2];

	ch[0] = 'A'; // if you did (char) 'A' + 1 you would get 'B'
	ch[1] = 'B'; // if you did (char) 'B' + 32

	printf("%c\n", ch[1]) //characters are stored as integers that has an ASCII value
	printf("%d\n", ch[1]) // shows the number
}