#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <semaphore.h>

// places the integer x on top of the stack
// Otherwise , err is set to non - zero value if the stack is full
void push ( struct stack * , int x , int * err ){
    return -1;
}

// removes and returns the integer on top of the stack
// Otherwise , err is set to non - zero value if the stack is empty
int pop ( struct stack * , int * err ){
    return -1;
}

// returns the integer on top of the stack
// Otherwise , err is set to non - zero value if the stack is empty
int peek ( struct stack * , int * err ){
    return -1;
}

// returns non - zero value when empty
int is_empty ( ) {
    return -1;
}


int student_main(int argc, char **argv)
{

    return 0;
}


/*
 * DO NOT MODIFY THIS MAIN FUNCTION
 */
int main(int argc, char **argv) // #151480
{
    return student_main(argc, argv);
}
