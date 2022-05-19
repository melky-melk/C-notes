#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// tells the computer dont optimise this, can change at anytime, is like a global variable?
volatile int interrupted = 0;

void impatient(int arg){
	interrupted = 1;
}

int main(){
	void (*variable) (int) = impatient; //created the function pointer as variable
	//if the program is interuppted e.g. someone hits ^C or ^X, then signal recognizes it has been interuppted. and will call the function impatient (which was stored in variable) 
	// if something has gone wrong wit that signal, then call the function it is just set p
	signal(SIGINT, variable) //it is just set up, ^C is a SIGINT, when that happend the function is called
	printf("We are going to do something for a long time\n");

	while (!interrupted)
		usleep(10);

	printf("Oh... you didnt like waiting\n");
	printf("Program terminated\n");
	
	return 0;
}