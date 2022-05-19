#include <stdio.h>

int main(void) {
	int x;
	double y;
	char buffer[20];
	
	// Check all three inputs are given 
	// the 19s makes sure that it is only 20 characters max, which is the size of the buffer
	// it is the maximum you are able to take
	if (scanf("%d %lf %19s", &x, &y, buffer) != 3) {
		fprintf(stderr, "Invalid input\n");
		return 1;
	}

	printf("%d %f %s\n", x, y, buffer);
	return 0;
}