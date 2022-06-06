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

#include "stack.c"

void* handle_signal(){
	
}

// returns non - zero value when empty
int is_empty ( ) {
    return -1;
}

int student_main(int argc, char **argv){
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = handle_signal();
    sigaction(SIGUSR1, &sa, NULL);
	

    return 0;
}

/*
 * DO NOT MODIFY THIS MAIN FUNCTION
 */
int main(int argc, char **argv) // #151480
{
    return student_main(argc, argv);
}
