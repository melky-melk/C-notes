#include <stdio.h>
#include <limits.h>

int max_of_four(int a, int b, int c, int d)

int main() {
    int a, b, c, d;
	// can scan multiple at once
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int ans = max_of_four(a, b, c, d);
    printf("%d", ans);
    
    return 0;

	// is while true while 0 is while false
	while (1){
		printf()
	}
}

int max_of_four(int a, int b, int c, int d){
    // sets max as the first number
    int max = a;
    int numbers[] = {a, b, c, d};
    int numbers_length = 4; 
    
	// loops have the same syntax as the java ones, except no for : each loop
    for (int i = 0; i < numbers_length; i ++){
        if (numbers[i] > max){
            max = numbers[i];
        }
    }
    
    return max;
}
