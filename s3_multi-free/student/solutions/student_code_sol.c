#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "student_code_sol.h"

/*
 * Frees all the memory associated with u
 * @pre: u != NULL
 */
void free_all_sol(university_t* u){
    if(u->rector != NULL){
        if(u->rector->name != NULL){ 
            free(u->rector->name);
        }
        free(u->rector);
    }
    if(u->city != NULL){
        free(u->city);
    }
    
    free(u);
}

/*
 * @return: a pointer to the university structure containing the elements
 */
university_t* init_all_sol(char* city, int creation, char* rectname, int age, int salary){
    //Assuming that the strings != NULL
	university_t* unif = malloc(sizeof(university_t));
	if(unif==NULL)
	    return NULL;
	char* ville = malloc(strlen(city)+1);
	if(ville==NULL){
	    free(unif);
	    return NULL;
	}
	strcpy(ville, city);
	unif->city=ville;
	unif->creation=creation;
	person_t* rector = malloc(sizeof(person_t));
	if(rector==NULL){
	    free(unif);
	    free(ville);
	    return NULL;
	}
	char* nom = malloc(strlen(rectname)+1);
	if(nom==NULL){
	    free(unif);
	    free(ville);
	    free(rector);
	    return NULL;
	}
	strcpy(nom, rectname);
	rector->name=nom;
	rector->age=age;
	rector->salary=salary;
	unif->rector=rector;
	return unif;
}
