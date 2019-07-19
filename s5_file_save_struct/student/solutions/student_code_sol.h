#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef struct point{
    int x;
    int y;
    int z;
} point_t;

int save_sol(point_t *pt, int size, char *filename);