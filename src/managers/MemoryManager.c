#include <stdio.h>
#include "stdlib.h"

void* allocateMemory(size_t size){ 
    return malloc(size);
}

void freeMemory(void* ptr){ 
    free(ptr);
}
