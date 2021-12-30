# How pointers work
You should consider pointers as if they are just another data type, it is the memory address of where variables are in the system

when you create a variable you both give it a value and the computer automatically gives it a memory address as well

for example when you do
```c
// value 30 gets stored on the computer, the ram of the memory, ite memory used when running programs. uses ram to keep track
// stores 30 in a specific memory location. in a physical memory of the computer
int age = 30;
double gpa = 3.4;
char grade = 'A';
```

to access the variable 30 we to refer to the name of the variable, i.e. age
whenever C needs to access it, it is going to refer to a memory address, when you type age it goes to the address in the memory and retrieves it from there

if we wanted to access the address of the variable age, we use an ampersand

```c
// do %p for pointer, to print the memory address. &age to access the physical memory address
printf("age: %p\n" age);
printf("age's memory address: %p\n", &age);
```

pointer is a type of data you can work with in programs
int is a number, decimal is a number, char is just a character
pointer is just a memory address, a number you can work with. like another type of data

# Dereferencing pointers
dereferincing pointers is when you go to the memory address the pointer is holding and you get the variable inside. Its accessing the actual value

we can make a pointer to the variable age by derefering it and giving it the memory address of the age variable
```c
int * pAge = &age;
```

now pAge stores only the pointer to age. but pAge also has its own pointer to itself (because all variables have a pointer to it's value) in this case pAge's value is age's pointer

pointer to pAge -> pAge -> age -> 30

to access the value of age through pAge you use the * to dereference it. this means it goes to the address inside pAge and accesses it.

pAge -> &age
pAge -> age = pAge -> 30

```c
printf("%d", *pAge)
// it is the same thing as this
// you get teh variable, go to the memory address of that variable using &, then use the * to dereference it and get what it is holding 
printf("%d", *&age)

// its called indirection, because you go through another step t
// POINTERS CONTAIN A PHYSICAL MEMORY ADDRESS AS TO WHERE THE VALUE OF THE VARIABLE IS LOCATED.  

// pointers allow you to return multiple values from a function

int * pnumber = NULL; //guarenteed not to point to anything 
```
# Double pointers

you can make a pointer variable and inside of that pointer you can store ANOTHER POINTER
when you make a pointer variable you would want to store an address that already exists in a program
when you create a variable you put an asterisk *p then the name of the variable who's memory address you are storing in