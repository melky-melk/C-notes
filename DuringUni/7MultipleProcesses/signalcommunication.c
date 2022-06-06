#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <time.h>

int x = 0; 

void handle_sigusr1(int sig){
	// if the user has still not typed out anything
	if (x == 0) {puts("\nHINT Remember that multiplication is repetitive addition");}
}

int main(int argc, char** argv){
	int fork_ret = fork();
	if (fork_ret == -1){
		return 1;
	}

	if (fork_ret == 0){
		// waits 5 seconds then sends signal to parent
		sleep(5);
		// if 5 seconds passes and the user doesnt get it, make the parent print a hint
		// gets parent process id and sends the signal SIGUSR is used for whatever operation you want. it is generic process operations
		kill(getppid(), SIGUSR1);
	}

	else {
		// waits for a signa; 
		struct sigaction sig;
		sig.sa_flags = SA_RESTART; //want to restart scanf once you finish execution
		sig.sa_handler = &handle_sigusr1;

		// binds to the 
		sigaction(SIGUSR1, &sig, NULL);

		// parent process
		printf("What is the result of 3 * 5\n");
		scanf("%d", &x);

		if (x == 15){puts("correct");}
		else {puts("incorrect");}
	}
	return 0;
}