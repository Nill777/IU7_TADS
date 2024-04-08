#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>

#define MAX_LEN_ARR 10000

// typedef struct person_t person_t; 

// struct person_t
// {
//     const char *name;
//     int born_year;

//     person_t *next;
// };

typedef struct node_t node_t;
struct node_t
{
    node_t *next;
    int val;
};

unsigned long long cur_mks_gettimeofday(void);
void clean_stdin(void);
void free_list(node_t *list);
int fscanf_exp(char *src, node_t **list, node_t **pl, int *stack_arr, int **ps, size_t print_flag);
int input_exp(node_t **list, node_t **pl, int *stack_arr, int **ps);
int print_stack_arr(int *stack_arr, int *ps, int i);
int print_stack_list(node_t *stack_list, node_t *pl, int i);
int calc_exp_arr(int *stack_arr, int *ps, size_t print_flag);
int calc_exp_list(node_t *stack_list, node_t *pl, size_t print_flag);
void efficency_table(void);

int push_stack_arr(int *stack_arr, int **ps, int el);
int pop_stack_arr(int *stack_arr, int **ps, int *el);
int push_stack_list(node_t **list, node_t **pl, int el);
int pop_stack_list(node_t *list, node_t **pl, int *el);
/*
int input_matrixs(int ***m_1_classic, int ***m_2_classic, int *row, int *col, matrix_t *m_1, matrix_t *m_2, size_t *count_el);
void print_matrix(matrix_t m, size_t count_el, int col);
int print_matrixs(matrix_t m_1, matrix_t m_2, size_t count_el, int col);
int summary_matrix_classic(int **m_1_classic, int **m_2_classic, int row, int col, size_t print_flag);
int summary_matrix(matrix_t m_1, matrix_t m_2, size_t count_el, int col, size_t print_flag);
void efficency_table(void);
*/
#endif
