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

int main(void){
    char str[50];
    char rev[50];

    printf("Enter any string : ");
    scanf("%s",str);
	
	rev_string(str, rev);
	
	printf("Reverse of string is : %s\n",rev);
  
    return 0;
}
