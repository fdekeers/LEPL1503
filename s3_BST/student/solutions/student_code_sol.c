#include <stdio.h>
#include <stdlib.h>
#include "student_code_sol.h"


int contains_node_sol(node_t* n, int value){
    if(!n) return 0;
    if(n->value == value) return 1;
    if(n->value > value) return contains_node_sol(n->left,value);
    return contains_node_sol(n->right,value); //if (n->value > value)
}


int contains_sol(bt_t* tree, int value){
    if(!tree) return 0;
    return contains_node_sol(tree->root,value);
}
