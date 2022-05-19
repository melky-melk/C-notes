is launching multiple threads that execute the same code but different sets of data

array with 6 elements, launch 6 threads 

parallelism is when they access their own memory, and not the same, they are workuing in parallel they dont interact with each other 

differences ebtween processes and threads

threads use the same id.

proccesses can contain multiple threads. 

all threads can access all variables

if you do anything in 1 thread you can see it in the other thread

sometimes threads can overlap on each other, and they will return weird 
https://www.youtube.com/watch?v=RY_2gElt3SA 

those are called race conditions



Task-parallelism: parallelism achieved from executing different
tasks at the same time (i.e., in parallel).
Data-parallelism: performing the same task to different data-items
at the same time

Dependencies impose a partial ordering on the tasks:
Two tasks Ta and Tb can execute in parallel iff
1) there is no path in the dependence graph from Ta to Tb
2) there is no path in the dependence graph from Tb to Ta