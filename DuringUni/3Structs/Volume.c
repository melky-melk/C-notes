#include <string.h>
#include <stdio.h> //used for reading and writing to a concole
#include <math.h> // need to include -lm at the end when you are compiling with math.h when you are using its functions
// it has pow(r, 3);

# define PI 3.1415

// a macro which is like mini function
# define CUBE(x) (x * x * x)

float sphere_volume(float radius) {
	return  (4.0/3.0) *  PI * CUBE(radius);
}

int main(){
	int radius;

	printf("Specify the radius of the sphere: ");
	scanf("%d", &radius);

	float volume = sphere_volume(radius);

	printf("Volume is: %.6f\n", volume);
	return 0;
}