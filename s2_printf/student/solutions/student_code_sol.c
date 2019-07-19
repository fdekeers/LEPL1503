#include<stdlib.h>
#include<stdio.h>

void print_foo_sol() {
    printf("foo\n");
}

void print_digit_sol(int number) {
    printf("The magic number is %d.\n", number);
}

void format_str_sol(char *buffer, unsigned int d, char *name, char initial) {
    sprintf(buffer, "Mister %s %c. has %d eggs", name, initial, d);
}
