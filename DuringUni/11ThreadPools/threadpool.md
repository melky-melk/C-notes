producers get the input, they take some input and turn it into the job for the consumers

consumers do the same thing they all of the things and the do them based on its input

producers make a job, and chuck it in the queue/enqueue it

the consumers then look at the queue, see if tehre is anything inside, if the queue is not empty. the consumer claims the job, 

consumers lock the queue then take the first job added, and do it. then wait for another job

you need to lock the queue before you do anything if there are multiple 

lock, dequeue if possible, unlock

producers create jobs add to queue, consumers 

pthread condition variables, its like a signal it can send to the consumer, so the program waits 

pthread wait function that waits till you can get a signal from the producer so the consumer loop isnt busy

```c
pthread_cond_wait(&condition, &mutex)
```

the mutex is the lock for the queue

condition representing that there is work in the queue

lock mutex

check if data is avaliable inside the queue, if there is nothing, lock it until you get a signal. 
```c
while (len(queue) == 0){
	// waits inside for here a signal?
	pthread_cond_wait(&condition, &mutex); //this unlocks the mutex and puts the mutex in the condition queue
}
```
they will all be in the condition queue

once the producer puts something in the work queue

it will take a random mutex in the condition queue and complete it

WE ARE LOCKING THE MUTEX TO CHECK IF THERE IS DATA AVALIABLE

in a while loop because it has the possiblility to wake up more than 1 thread (by accident) then will put them in the mutex lock queue

but because of the while loop it would check abother time the mutex would lock again 