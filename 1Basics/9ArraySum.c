# include <stdio.h>

int arraySum(int numbers[], const int length);
int pointerSum(int *numbers, const int length);

int main(){
    int arraySum(int numbers[], const int n);
    int values[10] = {3,7,3,-8,6,5,4,2,7,5};

    printf("the sum is %i\n", arraySum(values,10));
    printf("the sum is %i\n", pointerSum(values,10));
}

int arraySum(int numbers[], const int length) {
    // initiallise the pointer 
    int sum = 0, *pointer;
    int * const numbersEnd = numbers + length;

	// make the pointer be to be the first element of the array pointer = numbers
    // the end condition for the loop is not stated because once it reaches the end of the array
	// the pointer will be null, which is 0
    for (pointer = &numbers[0]; ++pointer){
        // add to the sum using the dereferenced pointer (which are just the numbers)
        sum += *pointer
    }

    return sum
}

int pointerSum(int *numbers, const int length){
	int sum = 0;
    int * const numbersStart = numbers;

	// dereferences where the pointer is currently at, and it gets incremented
	// once it reaches the end of the array, when the pointer is dereferenced it will be 0
	// meaning it will be false and the loop is exitted
    while (*number){
        sum += *numbers++;
    }

	// then reset
    numbers = numbersStart;
    return sum;
}
