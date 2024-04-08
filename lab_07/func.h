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


// Структура для элемента хеш-таблицы
typedef struct hash_node
{
    int key;
    int value;
    struct hash_node *node;
} hash_node_t;

// typedef struct node
// {
//     struct node_t *next;
//     hash_node_t node;
// } node_t;

// Структура для хеш-таблицы
typedef struct hash_table
{
    size_t size;
    hash_node_t **array;
} hash_table_t;

void clean_stdin(void);
int fill_tree(struct val_nodes *tree);
void print_node_name(tree_node_t *tree, void *param);
void print_node_val(tree_node_t *tree, void *param);
void export_to_dot(FILE *f, const char *tree_name, tree_node_t *tree, void (*print_node)(tree_node_t *, void *));
void apply_pre(tree_node_t *tree, void (*f)(tree_node_t*, void*), void *arg);
void apply_in(tree_node_t *tree, void (*f)(tree_node_t*, void*), void *arg);
void apply_post(tree_node_t *tree, void (*f)(tree_node_t*, void*), void *arg);
void print_name_node(tree_node_t *a, void *b);
int evaluate_postfix_expression(tree_node_t *node);
int cmp_tree_vs_stack(struct val_nodes tree);

void postfix_evaluation(tree_node_t *head);
void form_arr(tree_node_t *tree, int *arr);
tree_node_t* balance_BST(int *arr, size_t asize);
int create_node(tree_node_t **new_node, int data);
int create_table(hash_table_t *table, size_t size);
int create_open_htable(hash_table_t *table, size_t size);
void fill_hash_table(hash_table_t *table, int *a, size_t asize);
void fill_hash_table_open(hash_table_t *table, int *a, size_t asize);
tree_node_t* search_from_tree(tree_node_t *node, int data, size_t *cmp);
hash_node_t* search_from_hash_table(hash_table_t* table, int key, size_t *cmp);
hash_node_t* open_htable_search(hash_table_t* table, int key, size_t *cmp);
void print_hash_table(hash_table_t *table);
void print_open_htable(hash_table_t *table);
int cmp_tree_vs_table(void);

#endif
