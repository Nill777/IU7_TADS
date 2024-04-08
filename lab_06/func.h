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

typedef struct tree_node
{
    const char *name;
    int val;
    // родитель
    struct tree_node *parent;
    // меньшие
    struct tree_node *left;
    // большие
    struct tree_node *right;
} tree_node_t;

struct val_nodes
{
    tree_node_t sum_1;
    tree_node_t A;
    tree_node_t mul_1;
    tree_node_t B;
    tree_node_t sum_2;
    tree_node_t C;
    tree_node_t sum_3;
    tree_node_t sub_1;
    tree_node_t I;
    tree_node_t mul_2;
    tree_node_t sub_2;
    tree_node_t D;
    tree_node_t sum_4;
    tree_node_t G;
    tree_node_t H;
    tree_node_t E;
    tree_node_t F;
};

typedef struct node_t
{
    struct node_t *next;
    int val;
} node_t;

void clean_stdin(void);
int fill_tree(struct val_nodes *tree);
void export_to_dot(FILE *f, const char *tree_name, struct tree_node *tree);
void apply_pre(tree_node_t *tree, void (*f)(tree_node_t*, void*), void *arg);
void apply_in(tree_node_t *tree, void (*f)(tree_node_t*, void*), void *arg);
void apply_post(tree_node_t *tree, void (*f)(tree_node_t*, void*), void *arg);
void print_name_node(tree_node_t *a, void *b);
int evaluate_postfix_expression(tree_node_t *node);
int cmp_tree_vs_stack(struct val_nodes tree);

#endif
