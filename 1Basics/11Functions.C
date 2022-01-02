#include <stdio.h>

// its good practice to define the variables first at the top
int sum(int a, int b);

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    printf("the sum of the two is %d\n", sum(a, b));
    return 0;
}

int sum (int a, int b) {
    return a + b;
}