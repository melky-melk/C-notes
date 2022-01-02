#include <stdio.h>

int string_compare(const char* w1, const char* w2, unsigned int len);

int main(){
	int true_or_false = string_compare("melk", "hell", 4);
	printf("the strings are %s\n", true_or_false ? "the same" : "different");

	return 0;
}

int string_compare(const char* w1, const char* w2, unsigned int len){
	for (int i = 0; i < len; i++){
		
		if (*(w1 + i) != *(w2 + i)){
			return 0;
		}
	}
	
	return 1;
}