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
