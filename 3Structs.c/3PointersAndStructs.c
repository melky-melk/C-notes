#include <stdio.h>
struct person
{
   int age;
   float weight;
} Person;

int main()
{
    struct Person *personPtr, person1;
    personPtr = &person1; //makes the pointer at the person   

    printf("Enter age: ");
	// to access the value inside of a pointer/dereference use -> 
	scanf("%d", &personPtr->age);

    printf("Enter weight: ");
    scanf("%f", &personPtr->weight);

    printf("Displaying:\n");
    printf("Age: %d\n", personPtr->age);
    printf("weight: %f", personPtr->weight);

    return 0;
}