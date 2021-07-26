test: clean main.o module.o
	gcc -std=c99 -o test main.o module.o

main.o: main.c module.h
	gcc -std=c99 -c main.c

module_a.o: module.c module.h
	gcc -std=c99 -c module.c

.PHONY: clean

clean:
	rm -f *.o
	rm -f test
