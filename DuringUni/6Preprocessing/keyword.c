#include <stdio.h>
#include "other-file.c"

int x; //global variable for this file (other files can get this) 
extern int y; //takes a variable from another program
static int z; //global variable that can only be used in this file

int add(int a, int b); //local 
extern int multiply(int a, int b); //from a different file
int add(int a, int b){ 
	return a + b;
}
static int subtract(int a, int b); //in this file only
static int subtract(int a, int b){
	return a - b;
}

int f() {
	// like a global variable for this function
	// the a remembers the previous it was and increment
	static int a = 0;
	a++;
	printf("a = %d\n", a);
}

int main(void){
	for (int i = 0; i < 5; i++){
		f();
	}
	
	return 0;
}
