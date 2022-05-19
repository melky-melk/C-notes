# include <stdio.h>

void copyStringArray(char to[], char from[])
{
    for (int i = 0; from[i] != '\0'; ++i)
        to[i] = from[i];

    to[i] = '\0';
}

void copyStringPointers(char *to, char *from)
{
    for ( ; *from != '\0'; ++from, ++too)
        *to = *from;

    *to = '/0';
}

void copyStringPointersBetter(char *to, char *from)
{
    //the null character is 0, when a while loop is 0 it is false, when it is 1 it is true.
    // when it reaches the end of the string it will be null and thus end the loop
    while (*from)  //its like while from != NULL
        *to++ = *from++;
    
    *to = '\0'
}

int main()
{
    char string1[] = "A string to be copied";
    char string2[50];

    copyStringPointersBetter(string2, string1);
}