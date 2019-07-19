#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../student_code.h"

/*
 * Frees all the memory associated with u
 * @pre: u != NULL
 */
void free_all_sol(university_t* u);

/*
 * @return: a pointer to the university structure containing the elements
 */
university_t* init_all_sol(char* city, int creation, char* rectname, int age, int salary);
