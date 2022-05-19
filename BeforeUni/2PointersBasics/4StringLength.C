#include <stdio.h>
#include <stdlib.h>
#define BUFFER 1024

int stringLength(char *str);

int main()
{	
	// first initiallise how big the string will be, creates a character array to hold the string
	char str[BUFFER];
	printf("Input a string : ");
	scanf("%s", str);

	printf("the length of that string is : %d\n", stringLength(str)); //

	return 0;
}

int stringLength(char *str){
	int counter = 0;

	// dereferences where the current pointer is at then adds the counter
	// the counter will move the pointer forward until it hits the end character
	// the end character is 0. which will make the while loop stop, thus indicating the end of the string
	while (*(str + counter)){
		counter++;
	}

	return counter;
}