#include<stdio.h>

int main(){
    long value = 9999L;
	//makes the pointer to a constant long. so you cant change the long
	//  cannot change the value of the pointer, it cannot be reassigned
    const long *pvalue = &value;

    value = 7777l; //is valid, it changes the value the pointer is pointing to. but it doesnt use the pointer to change it so its allowed

    // the value of the pointer isnt a constant so you can change what it points to

    long newNumber = 69L;
    pvalue = &number;

    // if you want the pointer to be constant but the value can change then you would do
    int count = 42;
    int *const pcount = &count;

    int item = 34;
    pcount = &item; //will not work because the pointer is constant and you cannot change it

    /*
    const int * variableName // means the value cannot be changed
    int * const variableName  // means the pointer address cannot change
    */


	const char *fileheader = "P1";
	fileheader[1] = '3' //FIXME cannot change the data stored so this is incorrect

	// the adress of the character array is constant and channot be changed
	char * const fileheader = "P1"
	fileheader = "P3" //ddoesnt work because it changes the address? 
}