#ifndef MACROS_H
#define MACROS_H

#define ALLOC_STRUCT(stype) malloc(sizeof(stype))
#define ALLOC_N_OBJS(stype, count) calloc(count, sizeof(stype))

#endif