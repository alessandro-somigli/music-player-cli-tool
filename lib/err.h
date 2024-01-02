#ifndef ERR_H
#define ERR_H

#include <stdlib.h>
#include <stdio.h>

#define PRINTERR(STREAM, FORMAT, ...) do {              \
    fprintf(STREAM, "ERR %d: " FORMAT, __VA_ARGS__);    \
    exit(_GET_ERR(__VA_ARGS__));                        \
} while (0)

#define _GET_ERR(E, ...) E

#endif