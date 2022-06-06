pipe is an in memory file, a file that has a buffer saved in memory you write and read from it

pipes can only mainly be used for processes that are in the same hierarchy, i.e. parent child

it is only pathways

FIFOs are similar to pipes, a file type where you can read or write to any file type

its like a pipe which is not hierarchical

can make a fifo yourself in the terminal
```bash
mkfifo myfifo2
```

select() and pselect() allow a program to monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some class of I/O operation (e.g., input possible).  A file descriptor is considered ready if it is possible to perform a corresponding I/O operation (e.g., read(2), or a sufficiently small write(2)) without blocking.
```c
mkfifo(filename_for_fifo, the_mode) //the permissions you need for the file
```

# FIFO PERMISSIONS

every file has 3 permissions, the owner of the group, user permissions,  group permission. which are the permissions that applies to everyone in the bash group you can transport the permissions

every user that belongs to the group

owner is first 3 chars, group is next 3, other is next 3. what permissions does the ownder of the file have

first being read permission, write permissions, then execute permissions

if you were another group that was a part of "chiara" that was not "CHIARA-LAPTOP" you would be part of the next permissions, it would be the second permissions. the group permissions. 

0b111 111 000

meaning, owner can read, write, and execute, other people can read write execute, people who are not part of it cant read write or execute

//can use constants under
S_I

S_IRWXU | S_IRWXG

S_IRWXU is read write execute user
S_IRWXG is read write execute group
S_IRWXO is read write execute group but you can do all of them with 0777

0b 111 000 000
0b 000 111 000

when you or them together you get
S_IRWXU | S_IRWXG

0b 111 111 000

but i think its better to do the binary files

mainly just do owner and group? 


**USE UNLINK TO DELETE THE FIFOS**

# ECHO COMMANDS

echo dngjkehgoehgfoe > mypipe 

put input into a file.txt
then cat file.txt > mypipe

if you close standard out there will be a whole, 

if you make a new fd, by duplicating an old pipe, it will go where the stdout once was and will then replace it

so anytime you go to printf() you would print to that filedescriptor instead