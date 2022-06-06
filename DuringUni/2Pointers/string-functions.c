#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int main(){
	//strtok essentially returns the pointer to the
	char* line = "MELK LIME LEMON BEAN\n";

	// feeds the line into the str tok where it is saved
	char* command = strtok(line, " ");
	// when you want the next word to be saved, use null to move the line forward
	char* next_command = strtok(NULL, " ");
	// can also use str seperate to remove it
	char* token = strsep(&command, "\n");

	// find whether there is a substring within the larger string
	strstr(line, "BEAN");

	//strcspn counts up to the string
	int bean_num = strcspn(command, "BEAN");

	// sets the string to cut off early by using a null character
	command[strcspn(command, "\n")] = 0;
}