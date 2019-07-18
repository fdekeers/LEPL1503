#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "student_code.h"

/*
typedef struct product {
    char *name;
    double price;
} product_t;
*/

/*
 * @ptrProd != NULL
 * @return: the price of the product ptrProd
 */
double getPtrPrice(product_t *ptrProd){
    return ptrProd->price;
}

/*
 * @return: the price of the product prod
 */
double getPrice(product_t prod){
    return prod.price;
}

/*
 * @ptrProd != NULL
 * @name in ptrProd != NULL
 * @return: the name of the product ptrProd or NULL if an error happens
 */
char* getPtrName(product_t *ptrProd){
    char* ret = malloc(sizeof(char)*(strlen(ptrProd->name)+1));
    if(ret)
        strcpy(ret,ptrProd->name);
    return ret;
}

/*
 * @name in prod != NULL
 * @return: the name of the product ptrProd or NULL if an error happens
 */
char* getName(product_t prod){
    char* ret = malloc(sizeof(char)*(strlen(prod.name)+1));
    if(ret)
        strcpy(ret,prod.name);
    return ret;
}

/*
 * @ptrProd != NULL
 * @name in ptrProd != NULL
 * @name in prod != NULL
 * @return: 1 if the two products are the same
 */
int prodEquals(product_t *ptrProd, product_t prod){
    int nameEquals = !strcmp(ptrProd->name, prod.name);
    int priceEquals = ptrProd->price == prod.price;
    return nameEquals && priceEquals;
}
