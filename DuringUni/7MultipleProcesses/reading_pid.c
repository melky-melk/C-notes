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

int alt_getting_pid(char* process_name){	

	//  The  popen()  function opens a process by creating a pipe, forking, and invoking the shell.  Since a pipe is by definition unidirectional, the type argument may specify only reading or writing, not both; the resulting stream is correspondingly read-only or write-only.

	char pidof_process_name[strlen("pidof ") + strlen(process_name) + 1];
	strcat(pidof_process_name, "pidof ");
	strcat(pidof_process_name, process_name);

	//pidof is a command you can run to see something in a terminal, it opens a file of what the terminal output from there?
	FILE *cmd = popen(pidof_process_name, "r");
	
	pid_t trader_pid;
	fscanf(cmd, "%d", &trader_pid);
	pclose(cmd);

	return trader_pid;

	// can also use fgets
	// char pid_in_command[256];
	// fgets(pid_in_command, 256, cmd);
	// pid_t trader_pid = strtoul(pid_in_command, NULL, 10);
	// pclose(cmd);
}

int main(int argc, char **argv) {
	// need to set this up so it can define how a signal is recieved before it forks
    struct sigaction sa;
    printf("PID: %d\n", getpid());
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = get_signal_sender_pid;

    int pid = fork();
    if (pid < 0) {
        printf("Parent: error forking\n");
        return 1;
    }

    if (pid == 0) {
        kill(getppid(), SIGUSR1);
        return 0;
    }


    sigaction(SIGUSR1, &sa, NULL);
    pause();
    printf("Parent: PID of signal sender = %d\n", signalPid);

	printf("pid of bash is %d\n", alt_getting_pid("bash"));

    return 0;
}