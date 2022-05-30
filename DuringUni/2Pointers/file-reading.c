#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

int main(int argc, char** argv){
	// "r" "w" and "rb" works, read binary
	FILE* file_ptr = fopen("filename.txt", "r");
	char buffer[50];
	int chars_read = 50;

	//keeps reading until its an EOF
	// reads exactly how many characters until it hits a new line character or there are no mroe things to read 
	//  reads  in  at  most one less than size characters from stream and stores them into the buffer pointed to by s.  Reading stops after an EOF or a newline.  If a newline is read, it is stored into the buffer.  A terminating null byte ('\0') is stored after the last character in the buffer.
	while (fgets(buffer, chars_read + 1, file_ptr) != NULL) {
		printf("read from file: %d\n", buffer);
	}

	int number;
	fscanf(file_ptr, "%d", &number);

	// The function feof() tests the end-of-file indicator for the stream pointed to by stream, returning nonzero if it is set.  The end-of-file indicator can be cleared only by the function clearerr().
	feof(file_ptr);

	fclose(file_ptr);
}