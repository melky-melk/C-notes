```makefile
# can make variables in the files like in bash 
CFLAGS = -Wall -Werror -Wvla -fsanitize=address,leak
DEBUG = -fsanitize=address -g
CC = gcc

all: main 

add.o: add.c
	gcc -c add.c -o add.o

main.o: main.c
	gcc -c main.c -o main.o

main: add.o main.o
	gcc $(CFLAGS) $^ -o $@ # $^ this will copy all of the dependancies into the script, $@ will copy the name of the makefile
	# gcc $(CFLAGS) add.o main.o -o main

clean: 
	rm -f add.o main.o main #the f just forces it to do remove the files
```

```sh
make add.o
make main.o
```

make files make object files based on the dependancies

in this case, add.o's dependancy source code is add.c

`make main`

to make main, it would compile the object files together, into 1 binary file, main
it looks at the dependancies of main, add.o and main.o, if it doesnt have those dependancies in the file its in already, it tries to find them in the makefile, and make them 

chanig the make file doesnt change the dependancies even when you add flags, you would have to delete the current main

`make clean`
will remove all files

`make`
will run everything for you, its is essentially what all: main, defined, just put in the final product after the all: -insert final-

can make main and make main debug