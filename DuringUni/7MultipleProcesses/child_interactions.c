#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <time.h>

// global variable fork return 
pid_t fork_ret;

static void child_interrupt(int sig) {
    printf("child: Oh shoot no!\n");
}

void print_current_time() {
    time_t x;
    time(&x);
    printf("parent: %s", ctime(&x));
}

static void parent_interrupt(int sig) {
    print_current_time();

    printf("parent: ok insolent child. now tell me have you finished your homework?\n");
    if (fork_ret > 0) {
		// sends a signal to the fork return value (if it is a parent then the fork return value is the new process made i.e. the pid of the child process)
        kill(fork_ret, SIGINT);
    } else {
        puts("o no child invalid");
    }
}

int main(void) {
	// prints this before forking
    puts("about to fork");
    fork_ret = fork();

	// fork is less than 0 if something goes wrong
    if (fork_ret < 0) {
        puts("unable to fork");
        return 1;
    }

	// if the fork return is 0 that means the current process is the child
    if (fork_ret == 0) {
		// it sets up so that whenever it recieves a sig int it will print the child interupt
        signal(SIGINT, child_interrupt); // man 2 signal

        puts("child: Hey whatsup parent? Can you please tell me the time?");
		// gets the parent pid and gives it the kill signal
        kill(getppid(), SIGINT); // man 2 kill

        pause();
    } 
	
	// otherwise it is the parent process (the fork return value here would be the pid of the child process)
	else {
		// when given the signal by the child (above) it will do the parent interupt which will give child a signal
        signal(SIGINT, parent_interrupt); // man 2 signal

		// it waits for the child to finish until then it pauses
        pause();
        // wait(NULL);
    }
    return 0;
}
