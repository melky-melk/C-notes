#include <stdio.h>
#include <stdlib.h>

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
} melk, bean, lime, lemon, gang[4]; //make sure to include the semicolon and declare varibles here

// function prototype
void printInfo(struct Person person);

int main()
{
	// assign value to name of person1
	strcpy(melk.name, "Chiara");
	strcpy(bean.name, "Emily");
	strcpy(lime.name, "Taisia");
	strcpy(lemon.name, "Leo");
	
	strcpy(melk.onlineName, "melk");
	strcpy(bean.onlineName, "beab");
	strcpy(lime.onlineName, "lime");
	strcpy(lemon.onlineName, "lemon");

	strcpy(melk.occupation, "Uni Student");
	strcpy(bean.occupation, "High School Student");
	strcpy(lime.occupation, "Uni Student");
	strcpy(lemon.occupation, "High School Student");

	melk.age = 18;
	bean.age = 18;
	lime.age = 18;
	lemon.age = 18;

	printInfo(melk);
	printInfo(bean);
	printInfo(lime);
	printInfo(lemon);

	gang[0] = melk;
	gang[1] = bean;
	gang[2] = lime;
	gang[3] = lemon;

	return 0;
}

void printInfo(struct Person person) {
	printf("\n------------Displaying information------------\n");
	// print struct variables
	printf("Name: %s\n", person.name);
	printf("Online Handle: %s\n", person.name);
	printf("Occupation: %s\n", person.name);
	printf("Age: %s\n", person.name);
}