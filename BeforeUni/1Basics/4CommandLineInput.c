#include <stdio.h>

//to get input from the command line specify it in the main
int main(int argc, char *argv[]){
	char name[20];
	
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