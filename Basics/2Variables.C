#include <stdio.h>
// to define static variables
#define BUFFER 1024

int main(){
    // there are no stings only character arrays, stores a bunch of characters inside a variable
    char realName[] = "Chiara";
    char onlineName[] = "melk";
    int age = 18;
    // how to do constant variables in C, you cannot now change the variable PI to be something else
    const double PI = 3.14;

    // i dont think you can do string concatenation...
    printf("Hello I am %s\n", realName);
    printf("I am also known as %s\n", onlineName);
    printf("I am %d years old\n", age);
}