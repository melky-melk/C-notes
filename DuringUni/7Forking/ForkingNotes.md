a process is the whole binary file being executed

ps command looks at all the processes running on the computer

when ur computer starts lots of different processes start. the process that run initially runs init now called systemd

pstree shows what processes spawned in the beginning and howed what they spawned and so on, its a tree of everything being created

a c program runs as a process lowest memory to highest

program text
data
variables
heap memory
memory mapped
stack memory
environment and args

if you look at compiled binaryies

readelf --section <your compiled program>

objdump -D -M intel <your compiled program>
will convery the binary into assembly

string literals in compiled bynary

strings <compiled binary>
will print all ascii strings in the binary

# Using fork

ps will do this terminal processes, ps will show all terminal processes

fork starts at where it was called, it branchs from there rather than at the beginning. it uses the program counter, what execution is done next, the thing to be done next. The program counter is also cloned

fork is a system call like read or write, when you use it. the os creates a new process which is an exact clone of the current process, it has the same global and stack variables as the current process, from the moment you clone something the memory that changes is different. 

the process that calls fork is the parent, the clone is the child 

if you call a print in a fork function, then it will be printed twice. because there is 2 processes doing the same thing

if you want the child one to do something different to the original, you can use the return value of fork to differentiate the processes

if fork fails, then it will be less than 0

if it is not something negative and not 0, then the program is the parent 

memory for each process is different, the variables are seperated, one affected in the fork wont affect the parent

dont know which comes first, the child or the parent can come first. and the order the prints come in and the order the statements are executed are random one file doesnt finish before another

the return value of 

can get pid before forking, then when you fork the process you can compare the pid before forking to after forking. then if they match it is the parent process

the fork return value is the same pid as the child and the fork return value is

THE PARENT DOES NOT WAIT FOR THE CHILD TO FINISH

IF YOU FORCE THE PARENT NOT TO EXIT, AND THE CHILD HAS FINISHED EXECUTION. THE CHILD TURNS INTO A ZOMBIE PROCESS, SO THE CHILD IS DEAD AND FINISHED, BUT THE PARENT HAS NOT BROUGHT THE CHILD BACK IT IS STILL IN THE PROCESS TABLE. the parent think it still has a child process and does not remove it from the table

they vanish not because the parent waited for the child, the child goes to the init process that will reap the child. a process already called needs to reap the child.

as long as the parent is running other processes

it should use the command 
```c
#include <sys/wait.h>

wait(NULL);
waitpid(pid, NULL, 0);
waitpid(fork_ret, NULL, WNOHANG | WOOHAT);
```

takes a pointer to an integer but we mainly just **NULL**
to wait for ONE child processes (the original one?, the fork return value) to finish before proceeding. it will not wait for all processes

# SIGNALS
can use signals to communicate between processes

can override signals. for the parent/


whenever the parent gets sig int it means the child is asking for the time

whenever child gets sig int, child should print no 

child can send a sig interrupt to the parent.

once the parent prints the time. it can send a sig in to the child

waitpid, getpid, kill, pause

getpid, gives current process id

getppid can get the pid of the parent process 

pause stops the program until it recieves a signal

to ask the child/communicated kill(pid, SIGINT); which will have the pid of the child

signal says that whenever you get a sig int you will run the function pointer given

sigaction, tehre is 2 ways to hangle the signal handler, one is to make a struct and signal handler and the other is just signal(SIGINT, child interuppt))

kill whatever signal you want to whatever process if you give it
<!-- man 2 kill -->
<!-- man 2 signal -->

when you do control c it sends to both the parent and the child

# TERMINAL IN C

THE SHELL FORKS EVERY TIME IT NEEDS TO RUN A PROCESSES

exec() completely replaces your current process with another command that can be run in the terminal. 
to use the terminal inside of C

execl() takes in a pathname "/usr/bin/cat" to the actual binary file of where it is being

then give it the arguements given to the terminal

execl("/usr/bin/cat", "cat", "filename", NULL)

last argument must be a null 

after the program calls the exec the c process gets replaced with exec

strtok keeps the first thing saved
strsep takes the arguement and does it, it also changes the pointer

in strtok you have to call strtok(NULL, " "); to do the next one
sprintf(cmd_path, "/usr/bin/%s", cmd); //normal printf but instead of printing it saves the value

snprintf, will give a max size. and it will never try to write more than maxlen characters

using an & at the end of a terminal argument, the process will run in the background