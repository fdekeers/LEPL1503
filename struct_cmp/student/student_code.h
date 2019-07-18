typedef struct product {
    char *name;
    double price;
} product_t;

double getPtrPrice(product_t *ptrProd);

double getPrice(product_t prod);

char* getPtrName(product_t *ptrProd);

char* getName(product_t prod);

int prodEquals(product_t *ptrProd, product_t prod);
