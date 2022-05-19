#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
When a struct type is declared, no storage or memory is allocated. 
To allocate memory of a given structure type and work with it, we need to create variables.

p[] is a struct Person array of size 20.

// struct Person person1, person2, p[20];
*/

struct Person {
	char name[50];
	char onlineName[50];
	char occupation[50];
	int age;
} melk, bean, gang[4]; //make sure to include the semicolon and declare varibles here
// it initialises the gang as an array of 4 person
// and it declares variables some object variables so you dont need to write "struct Person melk;"

// function prototype
void printInfo(struct Person person);

int main()
{
	// assign value to name of person1
	strcpy(melk.name, "Chiara");
	strcpy(bean.name, "Emily");

	// bean = {.firstName = "Emily"}; //need to specify struct Person in front?

	// you can create an object if it follows the same attributes in order. 
	// it knows that name is leo and lemon is online name already
	struct Person lemon = {"Leo", "Lemon", 18};
	// you can be more specify however by doin the attributes and specifically putting it there
	struct Person lime = {.name = "Taisia", .onlineName = "Lime", 18};

	strcpy(melk.onlineName, "melk");
	strcpy(bean.onlineName, "beab");

	strcpy(melk.occupation, "Uni Student");
	strcpy(bean.occupation, "High School Student");

	melk.age = 18;
	bean.age = 18;

	gang[0] = melk;
	gang[1] = bean;
	gang[2] = lime;
	gang[3] = lemon;

	for (int i = 0; i < 4; i++) {
		printInfo(gang[i]);
	}

	return 0;
}

void printInfo(struct Person person) {
	printf("\n------------Displaying information------------\n");
	// print struct variables
	printf("Name: %s\n", person.name);
	printf("Online Handle: %s\n", person.onlineName);
	printf("Occupation: %s\n", person.occupation);
	printf("Age: %d\n", person.age);
}