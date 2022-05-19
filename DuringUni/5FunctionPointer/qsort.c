// qsort (array, sumber of elements, size of element, comparison_function_pointer)
#include <stdio.h>

typedef struct{
	int key;
	int other_data;
}record;

int record_compare(record const *a, record const *b){
	// returns a value? that will sort it? 
	return a->key - b->key;
}

int main(){
	// assuming you had an array
	qsort(array, arraylength, sizeof(record), record_compare);

	// function returning pointer to int
	// int *func(int a, float b);
	// function returning int
	// int (*func)(int a, float b);
}