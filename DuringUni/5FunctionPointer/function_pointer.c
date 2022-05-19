#include <stdio.h>
#include <string.h>

int sum (int x, int y) {return x + y;}
int minus (int x, int y) {return x - y;}

typedef int FunctionPointer(int, int);

int main(){
	// like in qsort, where it takes an array and length and a function pointer, then it uses the function you made and uses it to compare 2 elements, then sort them according to that function

	FunctionPointer *func_ptr = sum;

	int result = func_ptr(24, 1);

	printf("result of sum %d\n", result);

	// can now change the value of func_ptr
	func_ptr = minus;

	result = func_ptr(24, 1);

	printf("result of minus %d\n", result);
}