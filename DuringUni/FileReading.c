#include <stdio.h>

void read_file(FILE* fptr){
	while (1){
		// reads 1 character, so its only 1 character f get character so you dont need to give it a buffer
		// fread, how many items you want to read and the size of everyitem
		
		char ch = fgetc(fptr);
		
		// is a macro you get from stdio.h
		while (ch != EOF){
			putchar(ch);
			ch = fgetc(fptr);
		}
	}
}

int main(int argc, char **argv){
	FILE* fptr = stdin; //a file you can only read from but not write to. because this is just the console
	// c comes prequipped with this file
	
	if (argc <= 1){
		read_from_file(stdin);

		return 0;
	}

	for (int i = 1; i < argc; i++){
		fptr = fopen(argv[i], "r");
		read_from_file(fptr);
		fclose(fptr);
	}
}