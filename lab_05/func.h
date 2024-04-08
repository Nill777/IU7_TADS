#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>

#define MAX_SIZE 10000
#define LEN 1000

typedef struct item_t
{
    int number;
    size_t priority_queue;
    double time_in;
    double time_proc;
} item_t;

typedef struct node_t
{
    struct node_t *next;
    item_t val;
} node_t;

typedef struct queue_array_t
{
    item_t el;
    item_t arr[MAX_SIZE];
    size_t size;
    // head (delete)
    item_t *pin;
    // tail (insert) на запоследний
    item_t *pout;
    double t_in_max;
    double t_in_min;
    double t_proc_max;
    double t_proc_min;
} queue_array_t;

typedef struct queue_list_t
{
    node_t *head;
    node_t *tail;
    // char **p;
    // size_t count_pointers;
    size_t len;
    double t_in_max;
    double t_in_min;
    double t_proc_max;
    double t_proc_min;
} queue_list_t;


unsigned long long cur_mks_gettimeofday(void);
void clean_stdin(void);
void free_list(node_t *list);

int process_array(queue_array_t *a, queue_array_t *b);
int process_list(queue_list_t *a, queue_list_t *b);

int input_times(queue_array_t *a, queue_array_t *b, queue_list_t *c, queue_list_t *d);
void print_addresses(void);

#endif
