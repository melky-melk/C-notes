#include<stdio.h>

int main() {
    int num1;
    int num2;
    char symbol;
    
	printf("Enter a number an operator then the second number. e.g. 1 + 2: ");
    // make sure you use the ampersand so that it saves into the address of the variable
	scanf("%d %c %d", &num1, &symbol, &num2);
    
    int answer;
    printf("num 1 is %d \nnum 2 is %d\n", num1, num2);
    
	switch (symbol){
        case '+':
            answer = num1 + num2;
            break;
        case '-':
            answer = num1 - num2;
            break;
        case '*':
            answer = num1 * num2;
            break;
        case '/':
            answer = num1 /  num2;
            break;
    }

    printf("The answer is %d \n", answer);
    
    return 0;
}