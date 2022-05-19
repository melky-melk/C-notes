when compiling, the compiler goes through several stages

preprocesser -> assemblr -> linker

preprocessor can be seen when compiling with -E 
`gcc code.c -E`

assemblr can be seen when compiling with -S 
`gcc code.c -S`
assembler will show all of the variables, global and etc
it shows all sections and variables, still some things are needed for the object files

gcc -c 
will generate the necessary binary, and perform address information
objdump -s hello.o
to actually read it

linker will combine the object files with any addition symbols needed to make a .exe file you can run

create space where symbols are defined, with an associated address

main is a symbol (the main function you run)
when it gets to symbols it hasnt 

object files, are being merged by the linker file ld. 

when you compile a program tehre is a bunch of different steps

#include copies all the text and puts it in the compilier at the top

include guards are when they are already included, dont do it again, if its not defined include it and do it again

if the macro is not defined, then define it, otherwise dont include it

if printf can be defined as macros, if you have longs of printfs, you can sepeate some of the arguments as a new line??? **ask him later for an example**

MIN(a, b) (a < b ? a : b)

MIN(a++, 1) 

it would double increment the a++, so it would do it twice, if a is less than b, it would return a++ again

if a was -2

a++ will pass in minus 2 to the function
MIN(a++, 1)
after the function it will increment a to minus 1

the value the print gets is the unincremented value

```c
printf(%d, a++); //will print -2, but after a will give -1
```

if MIN was a function it would return -2

but, if MIN is a macro it will return 0 

when it evaluates a++ < 1
a is now -1

when it returns
a++ : 1

a is now 0

```c
#define DOUBLE(x) x + x

int a = 5;
DOUBLE(a) * 10 //will return 55 instead of 100, because there are no brackets around double so it will be 5 + 5 * 10, instead of (5 + 5) * 10 
```

like how java converts to .byte code, that can run on the java virtual machine

c compiles it to machine code that can run on the machine itself assembly

you cant read machine code, but you can convert it into somewhat readable, 

if you add the flag gcc -S, you can read it in assembly. its still the same, but you can read it in human values.
it compiles down t assembly

gcc -c will create a .o file, it is machine code but you cannot run it. it is all the file of the code you wrote, it does not contain anything from the standard library. there will be non of the linking and references in printf

you will get an undefined references
objdump -M to read it

need to link the standard library into the file, it just copy pastes all of the references to printf and directs it to the stdio.h file

gcc links the standard file to the library

we never define printf, but we just include, its not in our translastion unit, its something we link together at runtime

fopr functions and variables that do not exist within our translastion unit, we use the etern keyword

tells the compiler, that the thing we are going to use exists somewhere, so look for it in some of the other object files im compiling it with

printf doesnt exist within our files, in printf, it is declared as an extern function

extern basically tells the compiler, this function doesnt exist in the code compiling now, but it will exist in files later on (not use now, but will be used later)

when you use extern, when you compile them together you dont need extern, like the helper.h in assignment 2, i never used extern but i didnt need to. because i compiled ymirdb.c, it included and compiled together

if i tried to link the helper.h on its own it wouldnt work

when not using the standard library, you have to use int _start and not int main

when you have a library of functions, the standard. you have to use a header file, and the header file wont have declarations sdl.h

because that library is already compiled and packaged

source1.c
```c
int GLOBAL_VAL = 0;
```
source2.c
```c
extern int GLOBAL_VAL;
```

if you want to use something that exists outside of the code, you have to use extern

they would have to be linked together, not always in the same directory. you would just have to know the filepath or where it is so it can be linekd

static variables are like global variables, they are defined in global static space, so inside that function. 

```c
int f(){
	static int i = 0;
	i++;
	printf("%d\n", i);
}
```
set int i to be the static integer i, not local integer i

every time f is called, it will be incremented. when its called again, it will increment i again. because int i has already been assigned it will use the previous one

it is different from global because they have file scope, you cannot call static i in another file, like it cant be external. cannot get another static variable as an extern in another file

every function thats not static is global

if its not static, then other files know that its there, and it is global. static enforces privacy, like private to this file but global in the file

if you compiled gcc main.c add.c 

it would link together and you can use it
```c
#include <stdio.h>

int main(){
	printf("%d", add(5 + 7));
}
```

```c
int add (int a, int b) {return a + b;}
```

IT PUTS THINGS IN THE SAME BINARY FILE, all the functions from the includes are just added to the larger file

extern is mainly used when you make your own header file on itself without compiling with something else

extern is mainly used for global variables from other files

a declaration is when you tell the compiler when something exists, dont actually make it, it exists somewhere. definition is when you define a length

function definitions are something that has an actual body

declaration is when something already exists, dont make space for it because it is already tehre

definition is actually making space for it when it is already defined