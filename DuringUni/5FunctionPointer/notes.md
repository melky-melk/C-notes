# FUNCTION POINTERS

when an if statement is run, if the condition is false it will jump to the bit after the if statement

```c
int c = 33;
if (c == 33){
	c = 480 + 7
}
c += 768
```

so because the previous outcome was equal, it then runs the chunk of code inside the if statement
if not, it jumps to after 

if a function was called inside, i.e. print, function headings, there is a hump called

```c
int c = 33;
if (c == 33){
	c = 480 + 7;
	foo();
}
c += 768;
```

instead of jumping to the function, it is something called `call`
it is a pointer to a function, the area of memory where the function is stored. and you can change where that is stored.
a function pointer holds an address value 

to define a function pointer. return_type (*name_of_the_function_pointer) (parameters_for_function_types) = function_name
```c
int (*fptr) () = foo;
```

instead of calling foo, it will dereference fptr then call foo

uses of function pointers

reading from file, when it is finished, i want a function to call another piece of code

it would execute a new function call,

do something, if it goes wrong then call this function 

```c
if (x)
	funcA(x);
else
	funcB(b);
```

if you had say 3 different ways of printing things you can assign each of them a print style
```c
void printX_1 (int x) {printf("%d", x);}
void printX_2 (int x) {printf("%d\n", x);}
void printX_3 (int x) {printf("x: %d\n", x);}

//delegate which fn pointer. dan dynamically assign which function you want to do
if (user_style == PRETTY)
	print_style = printX_3;

//generic code
do_process(value1, print_style, remove_style);
```

function pointers kind of work how void pointers do.. you can replace a function pointer with different functions based on what you want

its like an overide for different kinds of functions

# SIGNALS

kill -9 

kill -s SIGKILL

kill -s SEGV (causes segmentation fault?)

# errno
this variable always exist
a global variable

will have an error number, wikll have the last failed operation