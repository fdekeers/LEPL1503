#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node{
    struct node *next;
    char *name;
};

int pop_sol(struct node **head, char *result);
int push_sol(struct node **head, const char *value);