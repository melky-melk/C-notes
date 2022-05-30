#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

//this is a signal handling variable to hold where the received PID will go
static volatile int signalPid = -1;

//this is a signal handling function to
void get_signal_sender_pid(int sign, siginfo_t *info, void *context) {
    signalPid = info->si_pid;
}

int main(int argc, char **argv) {
	// need to set this up so it can define how a signal is recieved before it forks
    struct sigaction sa;
    printf("PID: %d\n", getpid());
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = get_signal_sender_pid;
    sigaction(SIGUSR1, &sa, NULL);

    int pid = fork();
    if (pid < 0) {
        printf("Parent: error forking\n");
        return 1;
    }

	// this is the child process
    if (pid == 0) {
        //getpid() returns the PID for the process
        //printf("Child: Sending signal\nMy PID is %d\n", getpid());
        //getppid() returns the parent PID so we can signal the parent
        kill(getppid(), SIGUSR1);
        return 0;
    }

    pause();
    printf("Parent: PID of signal sender = %d\n", signalPid);

    return 0;
}