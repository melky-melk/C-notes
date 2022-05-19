#include <stdio.h>
#include <stdlib.h>

struct Person getInformation();
struct Person createPerson(char name[50], char onlineName[50], char occupation[50], int age);

// typeof makes the thing at the semicolon so it can make object
typeof struct person {
	char name[50];
	char onlineName[50];
	char occupation[50];
	int age;
} Person;

/* 
now you can create objects using the keyword person

Person p1;

instead of

struct person p1;
*/

// making a constructor
struct Person getInformation(){
	Person s1;

	printf("Enter name: ");
	scanf ("%[^\n]%*c", s1.name);

	printf("Enter online name: ");
	scanf ("%[^\n]%*c", s1.onlineName);

	printf("Enter occupation: ");
	scanf ("%[^\n]%*c", s1.occupation);

	printf("Enter age: ");
	scanf("%d", &s1.age);
	
	return s1;
}

struct Person createPerson(char name[50], char onlineName[50], char occupation[50], int age){
	Person p;

	strcpy(p.name, name);
	strcpy(p.onlineName, onlineName);
	strcpy(p.occupation, occupation);
	p.age = age;
	
	return p;
}