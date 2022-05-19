#include <stdio.h>

int string_compare(const char* w1, const char* w2, unsigned int len);

int main(){
	int true_or_false = string_compare("melk", "melk", 4);
	printf("the strings are %s\n", true_or_false ? "the same" : "different");

	return 0;
}

int string_compare(const char* w1, const char* w2, unsigned int len){
	
	// loops through the strings to a certain specified point
	for (int i = 0; i < len; i++){
		
		// keeps going until the strings dont equal, if they dont equal at any point then they are not equal
		if (*(w1 + i) != *(w2 + i)){
			return 0;
		}
	}
	
	// if it never returns 0 then it is true 
	return 1;
}