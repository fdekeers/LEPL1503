test: main.o module_a.o module_b.o
	gcc -std=c99 -o test $^

main.o: main.c module_a.h module_b.h
	gcc -std=c99 -c main.c

module_a.o: module_a.c module_a.h
	gcc -std=c99 -c module_a.c

module_b.o: module_b.c module_b.h
	gcc -std=c99 -c module_b.c

.PHONY: clean

clean:
	rm -f *.o
	rm -f test
