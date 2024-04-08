#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>

typedef struct
{
    int *A;
    int *JA;
    int *IA;
} matrix_t;

unsigned long long cur_mks_gettimeofday(void);
void clean_stdin(void);
void free_matrix(int **matrix, size_t n);
int fscanf_matrixs(char *src, int ***m_1_classic, int ***m_2_classic, int *row, int *col, matrix_t *m_1, matrix_t *m_2, size_t *count_el, size_t print_flag);
int input_matrixs(int ***m_1_classic, int ***m_2_classic, int *row, int *col, matrix_t *m_1, matrix_t *m_2, size_t *count_el);
void print_matrix(matrix_t m, size_t count_el, int col);
int print_matrixs(matrix_t m_1, matrix_t m_2, size_t count_el, int col);
int summary_matrix_classic(int **m_1_classic, int **m_2_classic, int row, int col, size_t print_flag);
int summary_matrix(matrix_t m_1, matrix_t m_2, size_t count_el, int col, size_t print_flag);
void efficency_table(void);

#endif
