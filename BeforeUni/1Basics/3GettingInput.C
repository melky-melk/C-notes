#include<stdio.h>

int main(){
    int age;
    // //getting input you use scanf
    printf("Enter your age: ");
    // // in order to get the input you need to put the & sumbol because it is a pointer allocating memory for it?
    // // it then stores the number given inside the age variable, it knows it is a number because you are using %d 
    scanf("%d", &age);
    printf("Only %d more years until you are 100!\n", 100 - age);

    // double gpa;
    printf("Enter your gpa: ");
    // // lf is for double
    scanf("%lf", &gpa);
    printf("Your gpa is %f\n", gpa);

    char grade;
    printf("Enter your grade: ");
    // c is for character 
    scanf("%c", &grade);
    printf("Your grade is %c\n", grade);

    // always need to input the size of the array of characters 
    // char name[] = "chiara"; //also works though, but when you have a variable that will change and will get an input, you need to specify the number 
    // if not given a value right away (like the chiara above) it will need a value
    char name[20];
    printf("Enter your name: ");
    // you dont need to put the ampersand because its an array its already allocated the amount of memory needed so you dont need to make a new pointer for it

    // if you put in "John smith" it will only save "John" as the name because it only reads until it hits a space bar
    scanf("%s", name);
    printf("Your name is %c\n", name);

    char fullname[20];
    // to cha cha real smooth past this, (the space bar thing) and just get the line of text, use fgets
    printf("Enter your full name: ");
    // this only works with a string, it cant get ints or doubles
    // limits the number of characters it gan get
    // also needs to specify that it is standard input 
    // fgets also gets the newline character, the extra enter 
    fgets(fullname, 20, stdin);
    printf("your full name is %s \n", fullname);

    return 0;
}