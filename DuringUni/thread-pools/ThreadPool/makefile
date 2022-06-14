CC=gcc
FLAGS=-Wall -Werror

test: test.c queue.c queue.h thread_pool.c thread_pool.h
	$(CC) $(FLAGS) $^ -o $@ -pthread

.PHONY: clean
clean:
	rm -f test