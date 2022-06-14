when you have lots of function calls within each other can cause a stack overflow 

if you have a lot of recursion, you want to allocate memory on the heap instead of the stack so there is more room on the stack to call the functions

stack frame is probably like a 32 bytes. 23,000 KB, 23MB things in the stack
chuck everything in a while true, then whatever is changing in your arguments/parameters in the function change those. make sure to save them initially

can ask the compiler to make recursive functions iterative? can compile in an optimised way, the compiler will assume stuff about the code and make it more efficient, compile with gcc recursion.c -o recursion -fsanitize=address -g -O2. the compiler compiles with O0 initially. But you need to trust that the compiler maintains that the code is correct, it would get quicker and work as expected. -O1 does some things, O2 takes a lot of liberties

O2 it would collapses it into one stack frame and would make recursive functions much MUCH faster, it wouldnt need to store things, it would use the stame stack frame. in thd iterative you have to increment s and decrriment len and keep track of them. in the other case you increment the argument by 1 and decriment by 2. 

its called tail call optimisation. will only work if it is static and inline? but that might be incorrect