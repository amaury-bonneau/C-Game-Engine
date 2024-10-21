#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdio.h>
#include "stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

void* allocateMemory(size_t size);
void freeMemory(void* ptr);
    
#ifdef __cplusplus
}
#endif

#endif