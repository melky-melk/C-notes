#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

// #include "stack.c"

#define read_end 0
#define write_end 1

struct stack{

};

//this is a signal handling variable to hold where the received PID will go
static volatile int signalPid = -1;

//this is a signal handling function to
void get_signal_sender_pid(int sign, siginfo_t *info, void *context) {
    signalPid = info->si_pid;
}

// places the integer x on top of the stack
// Otherwise , err is set to non - zero value if the stack is full
void push ( struct stack * head , int x , int * err ){
}

// removes and returns the integer on top of the stack
// Otherwise , err is set to non - zero value if the stack is empty
int pop ( struct stack * head, int * err ){
    return -1;
}

// returns the integer on top of the stack
// Otherwise , err is set to non - zero value if the stack is empty
int peek ( struct stack * head, int * err ){
    return -1;
}

// returns non - zero value when empty
int is_empty ( ) {
    return -1;
}

int student_main(int argc, char **argv){
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = get_signal_sender_pid;
    sigaction(SIGUSR1, &sa, NULL);
	
	int total_processes = atoi(argv[1]);
	int workers = atoi(argv[2]);
	int cleaners = atoi(argv[3]);

	int fd[2];
	if (pipe(fd) == -1){
		puts("an error occured with opening a pipe");
		return 1;
	}
	pid_t fork_ret = fork();
	pid_t parent_pid = getpid();
	struct stack* parent_stack = NULL;

	if (fork_ret == 0){
		close(fd[read_end]);
		
		// Worker - performs operations with the stack if is is not full or not empty.
		// Cleaner - performs operations with the stack when it is full or when it is empty. 
		// Cleaner processes cannot operate on the stack while Worker processes operate and vice versa.

		// for every worker it would try forking?
		for (int i = 0; i < workers; i++){
			fork_ret = fork();
			if (fork_ret != 0)
				break;
		}

		if (fork_ret != 0){
			for (int i = 0; i < cleaners; i++){
				fork_ret = fork();
				if (fork_ret != 0)
					break;
			}
		}

		// finished forking all of the process, all workers and cleaners
		wait(NULL);

		int command = rand() % 1;
		write(fd[write_end], &command, sizeof(int));
		kill(parent_pid, SIGUSR1);
		close(fd[write_end]);
	}

	// P0 with the main bit
	else {
		close(fd[write_end]);
		pid_t* all_processes = malloc(total_processes * sizeof(pid_t));

		int counter = 0;
		while (counter != atoi(argv[0])){
			pause();
			all_processes[counter] = signalPid;
			counter++;
		}

		while (1){
			pause();

			// check the counter which process it corresponds to
			counter = 0;
			for (int i = 0; i < total_processes; i++){
				if (signalPid == all_processes[i])
					break; 
			}
			
			int err = 0;
			int pop_command = -1;
			pop_command = read(fd[read_end], &pop_command, sizeof(int));
			// if the counter is within the range of the workers
			// then the signal came from a worker process
			if (counter < workers){
				if (pop_command)
					pop(parent_stack, &err);
				else
					push(parent_stack, 420, &err);
			}
			// otherwise its from cleaner process
			else {
				push(parent_stack, 420, &err);
				if (err != 0)
					pop(parent_stack, &err);
			}
		}

		free(all_processes);
		close(fd[read_end]);
	}

	return 0;
}

/*
 * DO NOT MODIFY THIS MAIN FUNCTION
 */
int main(int argc, char **argv) // #151480
{
    return student_main(argc, argv);
}
