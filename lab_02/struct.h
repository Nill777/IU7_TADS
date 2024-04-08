#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include "constants.h"

typedef struct
{
    char industry[MAX_LEN_INDUSTRY];
    size_t national;
    size_t translated;
    int year;
} technical_t;

typedef enum
{
    novel = 1,
    play,
    poetry1
} imaginative_t;

typedef enum {
    tales = 1,
    poetry2
} children_type_t;
typedef struct
{
    int age;
    children_type_t type;
} children_t;

typedef union
{
    technical_t tl;
    imaginative_t il;
    children_t cl;
} literature_t;

typedef enum {
    tl = 1,
    il,
    cl
} item_t;

typedef struct {
    char author[MAX_LEN_AUTHOR];
    char title[MAX_LEN_TITLE];
    char publish[MAX_LEN_PUBLISH];
    int pages;
    item_t type;
    literature_t item;
} library_item_t;

#endif
