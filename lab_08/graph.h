#ifndef GRAPH_H
#define GRAPH_H

#define MAX_SIZE 100
#define SIZE 100
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef enum
{
    NO_PATH = 1,
    LIST_ALLOC_ERROR,
    LIST_IS_NULL,
    READ_ERROR,
    STRING_TOO_SMALL,
    STRING_READ_ERROR,
    STRING_TOO_BIG,
    STACK_OVER_ERROR,
    STACK_DELETE_ERROR
} errors_t;

typedef struct graph
{
    int matrix[SIZE][SIZE];
    size_t size;
} graph_t;

typedef struct simple_path
{
    bool visited[MAX_SIZE];
    int path[MAX_SIZE];
    size_t size;
} simple_path_t;

int read_graph_from_file(graph_t *dst, const char *path_src);
void export_to_dot(FILE *f, const char *graph_name, graph_t *a);
void find_max_simple_path(graph_t *graph, simple_path_t *max_path_info);
void print_path(simple_path_t *info);
int is_graph_connected(graph_t *g);
int minimum_spanning_tree(graph_t *g);
void table_efficiency(void);

#endif