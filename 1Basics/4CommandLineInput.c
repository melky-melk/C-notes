#include <stdio.h>

//to get input from the command line specify it in the main
int main(char* argv[]){
	//whenever you want to get string input you have to make an array length for it
	// or can make an array pointer with an array
	char name[];
	
	printf("What is your name? ");
	scanf("%s", name);

	printf("%s %s\n", argv[1], name);
}

// for getting the number of arguments

int main(int num_of_args, char* args[]){
	for (int i = 1; i < num_of_args; i++){
		printf("%s ", args[i]);
	}
	printf("\n");

	return 0;
}