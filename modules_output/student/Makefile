test: main.o module_a.o module_b.o
	@gcc -o test $^
	@./test > output_sol.txt

main.o: main.c module_a.h module_b.h
	@gcc -o $@ -c $<

*.o: *.c *.h
	@gcc -o $@ -c $<

.PHONY: clean

clean:
	@rm -f *.o test
