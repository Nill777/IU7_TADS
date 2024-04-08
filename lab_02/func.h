#ifndef FUNC_H
#define FUNC_H

#include "struct.h"

void clean_stdin(void);
int fscan_string(char *dst, size_t max_len, FILE* file);
int fscan_technical(technical_t *dst, FILE *file);
int fscan_imaginative(imaginative_t *dst, FILE *file);
int fscan_children(children_t *dst, FILE *file);
int fscan_literature(library_item_t *dst, FILE *file);
void swap_literature(library_item_t *a, library_item_t *b);
void print_line(void);
void print_header(void);
void print_literature(library_item_t *src);
void copy_literature(library_item_t *dst, library_item_t const *src);
int remove_literature(library_item_t *arr, size_t *size, size_t ind);

#endif
