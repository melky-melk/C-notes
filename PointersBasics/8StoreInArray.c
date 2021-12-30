#include <stdio.h>
#include <stdlib.h>

int main(){
    int size, i;
    printf("Input the number of elements to store in the array : ");
    scanf("%d", &size); 

	// uses malloc to allocate the size of the array, it will make the size as much as it needs to be
    int * numberArray = (int *) malloc (size * sizeof(int));

	// loops through the number until the size is reached
    for (i = 0; i < size; i++){
        int element;
        printf("element - %d : ", i);
        scanf("%d", &element);

		// dereferences the pointer and gives it the value of the element that was just put in
        *(numberArray + i) = element;
    }

    printf("Printing the full array: {");

	// goes through the number array until it reaches the end and formats it
    for (i = 0; i < size - 1; i++){
        printf("%d, ", *(numberArray + i));
    }

    printf("%d}\n", *(numberArray + size - 1));

    free(numberArray);

    return 0;
}