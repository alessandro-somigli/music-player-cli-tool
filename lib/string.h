#ifndef STRING_H
#define STRING_H

#include <string.h>
#include <malloc.h>
#include "error.h"

typedef struct {
    char* str;
    size_t len;
} String;

#define STR(S) (String){S, sizeof(S)}

#define SSTR(N, S) do {                                 \
    (N).len = 1 + strlen(S);                            \
    (N).str = (char*)alloca((N).len * sizeof(char));    \
    memcpy((N).str, S, (N).len);                        \
} while (0)

#define DSTR(N, S) do {                                         \
    (N).len = 1 + strlen(S);                                    \
    (N).str = (char*)malloc((N).len * sizeof(char));            \
    if ((N).str != NULL) memcpy((N).str, S, (N).len);           \
    else PRINTERR(stderr, "D_STR copy err.\n", EXIT_FAILURE);   \
} while (0)

#endif
