anything that is hard coded into the string itself

by default, every numeric thing 
every decimal literal is a double
string literals are just strings?

if you want something to be other than the default you put like an `L` or a `U` or a `f` at the end of a number can only make a float literal, when it is already a double

type casting to an int will always round down, int divided by an integer will be an integer. it will truncate down

float f = 5/2 will be 2

everything is casted to a double if you have a double in an expression everything used in that is promoted to a double

then when its made into a float, its cased down to a float. but you can avoid the casting to doubles then float if you just made the 5.0 a float
```c
float f = 5.0f/2
printf("%f\n", f);
```

UNSIGNED CAN GO TO DOUBLE THE SIZE OF A REGULAR INT BECAUSE THEY USE THE FIRST BIT FOR THE SIGN THEN IT GOES BOTH WAYS 

when its -1 its all 1s for the 32 bytes, but when you cast it to unsigned, thats all 1s but positive so it goes to the highest one

`INT_MAX + 1` is INT_MIN

unsigned is above int in promotions


```c
printf("%d", 1U > -1); // evaluates to 0 (false) because the -1 is cast to an unsigned which is the largest possible number
```
we love unsigned integers
cuz it casts within the boolean expression

whatever has the bigger memory has more priority in the promotion

stdint.h is used to ensure compatibility, so you can choose the kind of ints you want to use

learn const better