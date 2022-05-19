#include <errno.h>

void foo(){
	FILE *fp = fopen("doesnt exist", "r");
}

int main(){

	perror("first line of code");

	foo();
	printf("errno: %d\n", errno);
	perror(""); //will print file not found

	errno = 0;

	int x = 5;
	printf("errno: %d\n", errno);
	perror(""); //still print file not found? 

	void* data = malloc(-1); //causes integer overflow, will try to allocate the largest space of memory possible
	printf("errno: %d\n", errno);
	perror("");

	free(data); //didnt allocate to begin with
	printf("errno: %d\n", errno);
	perror("");

	return 0;
}

// is set by the last function call that will set errno, can only store one function at a time
// set errno as 0 at the beginning of code, and when it is not 0, you know that an error has occured
// when fread and fwrite is interupped it will set errno based on the type of interuption