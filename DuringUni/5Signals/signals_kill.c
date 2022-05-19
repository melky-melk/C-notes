#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

void impatient(int arg){
	interrupted = 1;
}

// can be redefined like this
// typedef void (*sighandler_t) (int);

int main(){
	void (*old_signal_int_handler) (int) = impatient; //created the function pointer as variable
	int res;

	old_signal_int_handler = signal(SIGINT, interrupted) //default signalhandler is returned?
	printf("We are going to do something for a long time\n");

	if (old_signal_int_handler == SIG_ERR){
		perror("could not change signal handler");
		return -1;
	}

	char buffer [100];
	flag 0;
	ssize_t result = read(0, buffer, 100);

	int error_val = errno;

	if (error_val != 0){
		printf("\n error_val: %d\n", error_val);
		printf("read() was interrupted by a signal\n");
		printf("flag is: %d\n", flag);
		perror("hmm errno non zero -->");


		// can add something like, if (flag){} and do something about that
	}

	fprintf(stderr, "managed to read: %d characters\n", result);
	printf("buffer contains: ");
	for (int i = 0; i < result; i++)
		printf("_%c", buffer[i]);
	
	printf("\n");
	return 0;
}

// int kill(pid_t pid)