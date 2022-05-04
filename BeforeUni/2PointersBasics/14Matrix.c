#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    // both do the same thing this one creates an array of character arrays i.e. strings
    char names[][20] = {"Daniel", "Luke", "Oscar", "Alex", "Katrina"};

    // this creates a pointer to a bunch of character arrays that are next to each other
    char * pointerNames[20] = {"Daniel", "Luke", "Oscar", "Alex", "Katrina"};

	// double pointers for arrays are super fucking sketchy, it doesnt like it when you try to use a char* for a string 
	// much rather prefers an array for pointers
	// char **doublePointerNames = {"Daniel", "Luke", "Oscar", "Alex", "Katrina"};

	// you would need to individually put in each name for this one.
	char **doublePointerNames = (char *) malloc (20 * sizeof(char));

    for (int i = 0; i < 5; i++)
    {
        printf("array %s\n", names[i]);
		printf("pointer %s\n", *(pointerNames + i));
    }

    printf("%c\n", names[0][0]); //First character of the first name which is D

    // the pointer points to character arrays, rather than
    printf("%s\n", *pointerNames);
    //goes to the next character in the array, aniel instead of Daniel
	pointerNames[0] ++;
    printf("%s\n", *pointerNames);

    // names[2][1] = 'z';  // Again: will not work since names act as char*[20]

    // matrix[][3] would also work whereas matrix[][] will not
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    printf("%d\n", matrix[2][1]);

    // You need to specify columns or the compiler will not know when the next row starts
    // [1][2][3][4][5][6][7][8][9][][][][][][][][][][][][]
}