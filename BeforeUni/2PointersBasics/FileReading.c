#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 7

int main()
{
	FILE *fp; //size of an address
	// it fills in the details of what fp contains
	fp = fopen("swap.c", "r");
	if (fp == NULL){
		fprintf(stderr, "Couldn't open file");
		return 0;
	}

	char buffer[BUFFER];

	// will keep reading until something is wrong with the return value, and it returns null and exits
	while (1){
			// address of memory location to fill in
			// max size of memory in bytes
			// address of a file structure of an open stream
			// returns address of the buffer if successful

		// need to provide the area/address of memory you want the string to be written into
		// then the number size of the buffer
		// it needs the pointer to the file structure, the address where the memory is stored
		char* returnvalue = fgets(buffer, BUFFER, fp);

		// something has gone wrong with the file reading 
		if ( returnvalue == NULL || ret != buffer ){
			fprintf(stderr, "Couldn't open file");
			break;
		}

		for (int i = 0; i < BUFFER; i++){
			// prints the characters numeric value and the actual character
			printf("%d %c\n", buffer[i], buffer[i]);
		}

		printf("%s\n", buffer);
	}
	

	return 0;
}