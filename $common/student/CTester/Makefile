CC=gcc
SRC= CTester.c trap.c wrap_file.c wrap_getpid.c wrap_malloc.c wrap_mutex.c wrap_sleep.c
OBJ=$(SRC:.c=.o)
CFLAGS=-Wall -Werror -DC99 -std=gnu99

all: $(OBJ)
	
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $*.o $*.c 

clean:
	rm -f $(OBJ)

.PHONY: all

