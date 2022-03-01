#include <stdio.h>
#include <string.h>

void reverse_string(char* str, char* reverse) 
{
    // First pointer goes all the way to the end of the string
	while(*str) {str++;}

    // Pointer is at null terminator so take one step back
    str--;

    int i = 0;
    // Increase second pointer and decrease first pointer until the string length
    while (i < strlen(str))
    {
        *reverse = *str;
        reverse++;
        str--;
    }

    // Don't forget to add the null terminator
    *reverse = '\0';
}

void reverse_alternative() {
	char * startOfLine = (char *)malloc(50 * sizeof(char));

	printf("enter a string to reverse: ");
	fgets(startOfLine, BUFFER, stdin);
	char * endOfLine = startOfLine;

	// gets to the end of the string, till it hits the null and ends it 
	while (*endOfLine) {endOfLine++;}

	// printing the lines just to check if the pointers have moved
	printf("%p, %p\n", startOfLine, endOfLine);

	// then decriment the end of the line till it reaches the start again, then print the characters along the way
	while (endOfLine + 1 != startOfLine){
		printf("%c", *(endOfLine--));
	}

	printf("\n");
	
	free(startOfLine);
	// free(endOfLine); //dont need to free end of line because it is related to start of line?}
}

int main(void){
    char str[50];
    char rev[50];

    printf("Enter any string : ");
    scanf("%s",str);
	
	rev_string(str, rev);
	
	printf("Reverse of string is : %s\n",rev);
  
    return 0;
}
