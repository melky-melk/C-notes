#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_CMD_LEN 128

int main(void) {
	char cmd_buf[MAX_CMD_LEN];
	printf("$> ");

	// while there is still input
	while(0 != fgets(cmd_buf, MAX_CMD_LEN, stdin)) {
		if (cmd_buf[0] == '\n') {
			printf("$> ");
			continue;
		}
		
		// sets up values
		char* temp = cmd_buf;
		char* cmd = strsep(&temp, " \n");
		char* arg = strsep(&temp, " \n");
		printf("%s: %s\n", cmd, arg);

		char cmd_path[MAX_CMD_LEN];
		pid_t fork_ret = fork();
		
		// if the return value is 0, the current process is a child
		if (fork_ret == 0) {
			// formats the string so that it can be passed to the execute command, it gives a command length storage and the number
			snprintf(cmd_path, MAX_CMD_LEN, "/usr/bin/%s", cmd);

			// can use execv and pass an array of strings
			// to handle multiple args
			char* execv_args[3];
			execv_args[0] = cmd;
			execv_args[1] = arg;
			execv_args[2] = NULL;
			// can also use execl without the args and is all seperate arguments
			// execl(cmd_path, cmd, arg, NULL);
			if (execv(cmd_path, execv_args) == -1) {
				perror("exec failed");
				return 1;
			}
		} 

		// otherwise it waits for the child to finish processing 
		else {
			waitpid(fork_ret, NULL, 0);
		}
		printf("$> ");
	}
	printf("\n");
	return 0;
}