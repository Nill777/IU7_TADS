#define _POSIX_C_SOURCE 199309L
#include <stdlib.h>
#include "func.h"
#define COUNT_TESTS 100
#define SIZE 17
#define MAX_LEN_NAME 11

unsigned long long cur_ns_gettimeofday(void)
{
	struct timeval timeval;
	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000000000 + timeval.tv_usec * 1000);
}

unsigned long long get_time()
{
    struct timespec mt1;
    clock_gettime(CLOCK_REALTIME, &mt1);
    return 1000000000 * mt1.tv_sec + mt1.tv_nsec;
}

void clean_stdin(void)
{
    char c;
    while ((c = getchar()) != '\n');
}

int fill_tree(struct val_nodes *tree)
{
    int tmp;
    printf("Введите значение A:\n");
    if (scanf("%d", &tmp) != 1)
        return 1;
    tree->A.val = tmp;
    printf("Введите значение B:\n");
    if (scanf("%d", &tmp) != 1)
        return 1;
    tree->B.val = tmp;
    printf("Введите значение C:\n");
    if (scanf("%d", &tmp) != 1)
        return 1;
    tree->C.val = tmp;
    printf("Введите значение D:\n");
    if (scanf("%d", &tmp) != 1)
        return 1;
    tree->D.val = tmp;
    printf("Введите значение E:\n");
    if (scanf("%d", &tmp) != 1)
        return 1;
    tree->E.val = tmp;
    printf("Введите значение F:\n");
    if (scanf("%d", &tmp) != 1)
        return 1;
    tree->F.val = tmp;
    printf("Введите значение G:\n");
    if (scanf("%d", &tmp) != 1)
        return 1;
    tree->G.val = tmp;
    printf("Введите значение H:\n");
    if (scanf("%d", &tmp) != 1)
        return 1;
    tree->H.val = tmp;
    printf("Введите значение I:\n");
    if (scanf("%d", &tmp) != 1)
        return 1;
    tree->I.val = tmp;
    return 0;
}

void apply_pre(tree_node_t *tree, void (*f)(tree_node_t*, void*), void *arg)
{
    if (tree == NULL || f == NULL)
        return;

    f(tree, arg);
    apply_pre(tree->left, f, arg);
    apply_pre(tree->right, f, arg);
}
void apply_in(tree_node_t *tree, void (*f)(tree_node_t*, void*), void *arg)
{
    if (tree == NULL || f == NULL)
        return;

    apply_in(tree->left, f, arg);
    f(tree, arg);
    apply_in(tree->right, f, arg);
}
void apply_post(tree_node_t *tree, void (*f)(tree_node_t*, void*), void *arg)
{
    if (tree == NULL || f == NULL)
        return;

    apply_post(tree->left, f, arg);
    apply_post(tree->right, f, arg);
    f(tree, arg);
}
/*
void to_dot(tree_node_t *tree, void *param)
{
    FILE *f = param;
    if (tree->name[0] == '+' || tree->name[0] == '-' || tree->name[0] == '*' || !isalpha(tree->name[0]))
    {
        if (tree->left)
            fprintf(f, "\"%s\" -> \"%s\";\n", tree->name, tree->left->name);
        if (tree->right)
            fprintf(f, "\"%s\" -> \"%s\";\n", tree->name, tree->right->name);
    }
    else
    {
        if (tree->left)
            fprintf(f, "\"%d\" -> \"%d\";\n", tree->val, tree->left->val);
        if (tree->right)
            fprintf(f, "\"%d\" -> \"%d\";\n", tree->val, tree->right->val);
    }
}
*/
void to_dot(tree_node_t *tree, void *param)
{
    FILE *f = param;
    if (tree->left)
        fprintf(f, "\"%s\" -> \"%s\";\n", tree->name, tree->left->name);
    if (tree->right)
        fprintf(f, "\"%s\" -> \"%s\";\n", tree->name, tree->right->name);
}
// void to_dot_val(tree_node_t *tree, void *param)
// {
//     FILE *f = param;
//     if (tree->left)
//         fprintf(f, "\"%s\" -> \"%d\";\n", tree->name, tree->left->val);
//     if (tree->right)
//         fprintf(f, "\"%s\" -> \"%d\";\n", tree->name, tree->right->val);
// }

void print_node_name(tree_node_t *tree, void *param)
{
    FILE *f = param;
    fprintf(f, "\"%s\" [label=\"%c\"];\n", tree->name, tree->name[0]);
}
void print_node_val(tree_node_t *tree, void *param)
{
    FILE *f = param;
    fprintf(f, "\"%s\" [label=\"%d\"];\n", tree->name, tree->val);
}

void export_to_dot(FILE *f, const char *tree_name, tree_node_t *tree, void (*print_node)(tree_node_t *, void *))
{
    fprintf(f, "digraph %s {\n", tree_name);
    apply_pre(tree, print_node, f);
    apply_pre(tree, to_dot, f);
    fprintf(f, "}\n");
}
// void export_to_dot_val(FILE *f, const char *tree_name, struct tree_node *tree)
// {
//     fprintf(f, "digraph %s {\n", tree_name);
//     apply_pre(tree, print_node_val, f);
//     apply_pre(tree, to_dot_name, f);
//     fprintf(f, "}\n");
// }

void print_name_node(tree_node_t *a, void *b)
{
    (void) b;
    printf("%c", a->name[0]);
}

int evaluate_postfix_expression(tree_node_t *node) {
    int value;
    if (node != NULL) {
        if (isalpha(node->name[0]))
        {
            value = node->val;
            return value;
        }
        else
        {
            int left_val = evaluate_postfix_expression(node->left);
            int right_val = evaluate_postfix_expression(node->right);
            switch (node->name[0]) {
                case '+':
                    return left_val + right_val;
                case '-':
                    return left_val - right_val;
                case '*':
                    return left_val * right_val;
                // case '/':
                //     return left_val / right_val;
            }
        }
    }
    return 0;
}

int pop_stack_arr(int *stack_arr, int *ind_last, int *el)
{
    if (*ind_last - 1 < 0)
        return 1;
    *el = stack_arr[*ind_last - 1];
    (*ind_last)--;
    return 0;
}

int push_stack_arr(int *stack_arr, int *ind_last, int el)
{
    if (*ind_last >= 17)
        return 1;
    stack_arr[*ind_last] = el;
    (*ind_last)++;
    return 0;
}

int evaluate_postfix_expression_stack(int *res)
{
    int a, b;
    int ind_last_stack = 0;
    int stack_arr[SIZE];
    int expression[SIZE] = {1, 2, 3, 4, 5, 6, '+', '*', 7, 8, '-', '-', 9, '+', '+', '*', '+'};
    
    // stack
    for (size_t i = 0; i < SIZE; i++)
    {
        if ((char) expression[i] == '+')
        {
            if (pop_stack_arr(stack_arr, &ind_last_stack, &a))
                return 1;
            if (pop_stack_arr(stack_arr, &ind_last_stack, &b))
                return 2;
            if (push_stack_arr(stack_arr, &ind_last_stack, b + a))
                return 3;
        }
        else if ((char) expression[i] == '-')
        {
            if (pop_stack_arr(stack_arr, &ind_last_stack, &a))
                return 1;
            if (pop_stack_arr(stack_arr, &ind_last_stack, &b))
                return 2;
            if (push_stack_arr(stack_arr, &ind_last_stack, b - a))
                return 3;
        }       
        else if ((char) expression[i] == '*')
        {
            if (pop_stack_arr(stack_arr, &ind_last_stack, &a))
                return 1;
            if (pop_stack_arr(stack_arr, &ind_last_stack, &b))
                return 2;
            if (push_stack_arr(stack_arr, &ind_last_stack, b * a))
                return 3;
        }
        else
            if (push_stack_arr(stack_arr, &ind_last_stack, expression[i]))
                return 4;
    }
    if (ind_last_stack != 1)
        return 5;
    *res = stack_arr[0];
    return 0;
}

int cmp_tree_vs_stack(struct val_nodes tree)
{
    tree.A.val = 1;
    tree.B.val = 2;
    tree.C.val = 3;
    tree.D.val = 4;
    tree.E.val = 5;
    tree.F.val = 6;
    tree.G.val = 7;
    tree.H.val = 8;
    tree.I.val = 9;

    int res_stack = 0;
    unsigned long long start_time1;
    unsigned long long finish_time1;
    unsigned long long start_time2;
    unsigned long long finish_time2;
    
    unsigned long long avg_time1 = 0;
    unsigned long long avg_time2 = 0;
    
    printf("Тестирование проведено %d раз\n", COUNT_TESTS);
    puts("Время указано в наносекундах, затраты памяти в байтах\n");
    puts("TIME");
    for (size_t i = 0; i < 15 + 15 + 3; i++)
        printf("-");
    printf("\n|%15s|%15s|\n", "Stack", "Tree");
    for (size_t i = 0; i < 15 + 15 + 3; i++)
        printf("-");
    puts("");
    for (size_t i = 0; i < COUNT_TESTS; i ++)
    {
        start_time1 = cur_ns_gettimeofday();
        if (evaluate_postfix_expression_stack(&res_stack))
            return 1;
        finish_time1 = cur_ns_gettimeofday();

        start_time2 = cur_ns_gettimeofday();
        evaluate_postfix_expression(&tree.sum_1);
        finish_time2 = cur_ns_gettimeofday();

        avg_time1 += finish_time1 - start_time1;
        avg_time2 += finish_time2 - start_time2;
    }
    printf("|%15llu|%15llu|\n", avg_time1 / COUNT_TESTS, avg_time2 / COUNT_TESTS);
    for (size_t i = 0; i < 15 + 15 + 3; i++)
        printf("-");
    puts("\n");

    puts("MEMORY");
    for (size_t i = 0; i < 15 + 15 + 3; i++)
        printf("-");
    printf("\n|%15s|%15s|\n", "Stack", "Tree");
    for (size_t i = 0; i < 15 + 15 + 3; i++)
        printf("-");
    puts("");

    printf("|%15lu|%15lu|\n", (2 * SIZE + 3) * sizeof(int), sizeof(struct val_nodes));
    for (size_t i = 0; i < 15 + 15 + 3; i++)
        printf("-");
    puts("");
    return 0;
}



int evaluate_expression_tree(tree_node_t *node)
{
    switch(node->name[0])
    {
        case '+':
            return evaluate_expression_tree(node->left) + evaluate_expression_tree(node->right);
        case '-':
            return evaluate_expression_tree(node->left) - evaluate_expression_tree(node->right);
        case '*':
            return evaluate_expression_tree(node->left) * evaluate_expression_tree(node->right);
        default:
            return node->val;
    }
}

void postfix_evaluation(tree_node_t *tree) {
    if (!tree)
        return;

    postfix_evaluation(tree->left);
    postfix_evaluation(tree->right);

    tree->val = evaluate_expression_tree(tree);
}

// Получить массив, используя инфиксный обход
// полученного дерева.
size_t i;
void get_node_val(tree_node_t *tree, void *param)
{
    ((int *) param)[i] = tree->val;
    i++;
}
void form_arr(tree_node_t *tree, int *arr)
{
    i = 0;
    apply_in(tree, get_node_val, arr);
}

// Максимальная длина имени 10 символов
size_t name;
int create_node(tree_node_t **new_node, int data)
{
    char *str;
    if (!(*new_node = calloc(1, sizeof(tree_node_t))))
        return 1;

    if (!(str = calloc(MAX_LEN_NAME, sizeof(char))))
        return 2;
    sprintf(str, "%zu", name);
    (*new_node)->name = str;
    (*new_node)->val = data;
    (*new_node)->parent = NULL;
    (*new_node)->left = NULL;
    (*new_node)->right = NULL;
    name++;
    return 0;
}

// Функция для построения ДДП из массива
tree_node_t* sorted_arr_to_BST(int *arr, int ind_start, int ind_end) 
{
    if (ind_start > ind_end)
        return NULL;
    // Находим средний элемент массива и делаем его корнем дерева
    int ind_mid = (ind_start + ind_end) / 2;
    tree_node_t *node = NULL;
    if (create_node(&node, arr[ind_mid]))
        return NULL;
    // Рекурсивное построение левого и правого поддеревьев
    node->left = sorted_arr_to_BST(arr, ind_start, ind_mid - 1);
    node->right = sorted_arr_to_BST(arr, ind_mid + 1, ind_end);

    return node;
}

int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}
tree_node_t* balance_BST(int *arr, size_t asize)
{
    name = 0;
    qsort(arr, asize, sizeof(int), compare);
    return sorted_arr_to_BST(arr, 0, asize - 1);
}

// Построить хеш-таблицу для значений этого массива.
// Осуществить поиск указанного значения.
 
// Функция для поиска значения в ДДП
tree_node_t* search_from_tree(tree_node_t *node, int data, size_t *cmp) 
{
    (*cmp)++;
    // Если текущий узел является конечным узлом или данные совпадают, возвращаем текущий узел
    if (node == NULL || node->val == data)
        return node;
    if (data < node->val)
        return search_from_tree(node->left, data, cmp);
    else
        return search_from_tree(node->right, data, cmp);
}


int hash(int key, int size)
{
    return key % size;
}

int create_node_table(hash_node_t **node, int key, int value)
{
    if (!(*node = malloc(sizeof(hash_node_t))))
        return 1;
    (*node)->key = key;
    (*node)->value = value;
    (*node)->node = NULL;
    return 0;
}

// Функция для создания новой хеш-таблицы
int create_table(hash_table_t *table, size_t size)
{
    table->size = 2 * size;
    if (!(table->array = calloc(2 * size, sizeof(hash_node_t))))
        return 1;
    return 0;
}
int create_open_htable(hash_table_t *table, size_t size)
{
    table->size = size;
    if (!(table->array = calloc(size, sizeof(hash_node_t))))
        return 1;
    return 0;
}

// Функция для вставки элемента в хеш-таблицу(закрытое хеширование)
void hash_table_insert(hash_table_t* table, int key, int value)
{
    int iter = 0;
    // int index = hash(key, table->size / 2);
    // puts("%%");
    // Поиск свободного слота
    if (key < 0)
        key = -key;
    // printf("i %d\n", index);

    // (size_t) (index + iter * iter) < table->size && 
    while (table->array[key + iter * iter] != NULL)
    {
        iter++;
        // index = index + (iter * iter);
        // if (index < 0)
        //     index = -index;
    }
    key += iter * iter;
    // printf("i %d val %d\n", index, value);
    // if (table->array[index] != NULL && table->array[index]->key != key)
    // Если нашли свободный слот, вставляем элемент
    // Если элемент уже существует, обновляем его значение
    if (table->array[key] == NULL)
    {
        // printf("insert %d\n", index);
        create_node_table(&table->array[key], key, value);
    }
    else
    {
        // printf("change %d\n", key);
        table->array[key]->value = value;
    }
}

// Функция для вставки элемента в хеш-таблицу(открытое хеширование)
void hash_table_insert_open(hash_table_t* table, int key, int value)
{
    hash_node_t *tmp_node;
    hash_node_t *prev_node;
    // int index = hash(key, table->size / 2);
    // Поиск свободного слота
    if (key < 0)
        key = -key;
    if (table->array[key] != NULL)
    {
        prev_node = table->array[key];
        tmp_node = table->array[key];
        while (tmp_node->node != NULL)
        {
            prev_node = tmp_node;
            tmp_node = tmp_node->node;
        }
        create_node_table(&tmp_node, key, value);
        prev_node->node = tmp_node;
    }
    else
    {
        // printf("change %d\n", index);
        create_node_table(&table->array[key], key, value);
    }
}

// Функция для поиска элемента по ключу в хеш-таблице
hash_node_t* search_from_hash_table(hash_table_t* table, int key, size_t *cmp)
{
    int iter = 0;
    int index = hash(key, table->size / 2);
    if (index < 0)
        index = -index;
    (*cmp)++;
    while ((size_t) (index + iter * iter) < table->size && \
            table->array[index + iter * iter] != NULL && \
            table->array[index + iter * iter]->value != key) 
    {
        (*cmp)++;
        iter++;
    }
    if ((size_t) (index + iter * iter) < table->size)
    {
        index += iter * iter;
        return table->array[index];
    }
    else
        return NULL;
}

// Функция для поиска элемента по ключу в хеш-таблице
// key == search value
hash_node_t* open_htable_search(hash_table_t* table, int key, size_t *cmp)
{
    hash_node_t *tmp_node;
    int index = hash(key, table->size);
    if (index < 0)
        index = -index;
    (*cmp)++;
    tmp_node = table->array[index];
    while (tmp_node != NULL && tmp_node->value != key) 
    {
        (*cmp)++;
        tmp_node = tmp_node->node;
    }

    if (tmp_node != NULL && tmp_node->value == key)
        return tmp_node;
    else
        return NULL;
}

void fill_hash_table(hash_table_t *table, int *a, size_t asize)
{
    for (size_t i = 0; i < asize; i++)
        hash_table_insert(table, hash(a[i], asize), a[i]);
}

void fill_hash_table_open(hash_table_t *table, int *a, size_t asize)
{
    for (size_t i = 0; i < asize; i++)
        hash_table_insert_open(table, hash(a[i], asize), a[i]);
}

void print_hash_table(hash_table_t *table)
{
    puts("Хеш-таблица закрытого типа");
    for (size_t i = 0; i < 4 + 15 + 15 + 4; i++)
        printf("-");
    printf("\n|%6s|%15s|%15s|\n", "№", "Key", "Value");
    for (size_t i = 0; i < 4 + 15 + 15 + 4; i++)
        printf("-");
    puts("");

    for (size_t i = 0; i < table->size; i++)
        if (table->array[i])
            printf("|%4zu|%15d|%15d|\n", i, table->array[i]->key, table->array[i]->value);
        else
            printf("|%4zu|%15s|%15s|\n", i, "-", "-");

    for (size_t i = 0; i < 4 + 15 + 15 + 4; i++)
        printf("-");
    puts("");
}

void print_open_htable(hash_table_t *table)
{
    hash_node_t *tmp;
    puts("Хеш-таблица открытого типа");
    for (size_t i = 0; i < 4 + 15 + 15 + 4; i++)
        printf("-");
    printf("\n|%6s|%15s|%15s|\n", "№", "Key", "Value");
    for (size_t i = 0; i < 4 + 15 + 15 + 4; i++)
        printf("-");
    puts("");

    for (size_t i = 0; i < table->size; i++)
        if (table->array[i])
        {
            tmp = table->array[i];
            printf("|%4zu|%15d|%15d|\n", i, table->array[i]->key, table->array[i]->value);
            while (tmp->node != NULL)
            {
                tmp = tmp->node;
                printf("|%4s|%15d|%15d|\n", "", tmp->key, tmp->value);
            }
        }
        else
            printf("|%4zu|%15s|%15s|\n", i, "-", "-");

    for (size_t i = 0; i < 4 + 15 + 15 + 4; i++)
        printf("-");
    puts("");
}

#define AMOUNT_EL 1000
int cmp_tree_vs_table(void)
{
    tree_node_t *BST;
    hash_table_t open_htable;
    hash_table_t close_htable;
    srand(time(NULL));
    int arr[AMOUNT_EL];
    for (size_t i = 0; i < AMOUNT_EL; i++)
    {
        arr[i] = rand() % 100;
        // arr[i + 1] = arr[i] + AMOUNT_EL;
    }

    // int res_stack = 0;
    unsigned long long start_time1;
    unsigned long long finish_time1;
    unsigned long long start_time2;
    unsigned long long finish_time2;
    unsigned long long start_time3;
    unsigned long long finish_time3;

    printf("Тестирование проведено %d раз\n", COUNT_TESTS);
    puts("Время указано в наносекундах, затраты памяти в байтах\n");
    puts("TIME");
    size_t time_len = 6 + 31 + 31 + 31 + 5;

    for (size_t i = 0; i < time_len; i++)
        printf("-");
    printf("\n|%6s|%31s|%31s|%31s|\n", "", "Tree", "Close hash table", "Open hash table");
    for (size_t i = 0; i < time_len; i++)
        printf("-");
    printf("\n|%6s|%15s|%16s|%15s|%16s|%15s|%16s|\n", "N", "Time", "Сompare", "Time", "Сompare", "Time", "Сompare");
    for (size_t i = 0; i < time_len; i++)
        printf("-");
    puts("");

    for (size_t i = 100; i <= AMOUNT_EL; i += 100)
    {     
        for (size_t j = 0; j <= i; j += 2)
        {
            arr[j] = rand()%i + j;
            arr[j + 1] = arr[j] + (int) i;
            // printf("%d %d\n", arr[j], arr[j + 1]);
        }   

        unsigned long long avg_time1 = 0;
        unsigned long long avg_time2 = 0;
        unsigned long long avg_time3 = 0;
        size_t cmp_tree = 0;
        size_t cmp_table_1 = 0;
        size_t cmp_table_2 = 0;
        // for (size_t i = 0; i < AMOUNT_EL; i++)
            // arr[i] = rand();

        BST = balance_BST(arr, i);

        create_table(&close_htable, i);
        fill_hash_table(&close_htable, arr, i);

        create_open_htable(&open_htable, i);
        fill_hash_table_open(&open_htable, arr, i);
        // print_hash_table(&table);
        // if (i == 100)
        // {
        //     print_hash_table(&close_htable);
        //     print_open_htable(&open_htable);
        // }
        int search_val = arr[i - 1];
        // printf("%d\n", search_val);
        for (size_t k = 0; k < COUNT_TESTS; k++)
        {
            // start_time1 = cur_ns_gettimeofday();
            start_time1 = get_time();
            search_from_tree(BST, search_val, &cmp_tree);
            finish_time1 = get_time();
            // finish_time1 = cur_ns_gettimeofday();

            // start_time2 = cur_ns_gettimeofday();
            start_time2 = get_time();
            search_from_hash_table(&close_htable, search_val, &cmp_table_1);
            finish_time2 = get_time();
            // finish_time2 = cur_ns_gettimeofday();

            // start_time2 = cur_ns_gettimeofday();
            start_time3 = get_time();
            open_htable_search(&open_htable, search_val, &cmp_table_2);
            finish_time3 = get_time();
            // finish_time2 = cur_ns_gettimeofday();
            // printf("%d %zu\n", search_val, (i / 2) + 2);
            // if (tmp_0)
            //     printf("correct%d\n", tmp_0->value);
            // if (tmp_1)
            //     printf("correct%d\n", tmp_1->value);
            avg_time1 += finish_time1 - start_time1;
            avg_time2 += finish_time2 - start_time2;
            avg_time3 += finish_time3 - start_time3;
        }
        // printf("%d %zu\n", search_val, (i / 2) + 2);
        // print_hash_table(&close_htable);
        // print_open_htable(&open_htable);
        printf("|%6zu|%15llu|%15zu|%15llu|%15zu|%15llu|%15zu|\n", i, avg_time1 / COUNT_TESTS, cmp_tree / COUNT_TESTS, \
                                                                     avg_time2 / COUNT_TESTS, cmp_table_1 / COUNT_TESTS, \
                                                                     avg_time3 / COUNT_TESTS, cmp_table_2 / COUNT_TESTS);
    }
    for (size_t i = 0; i < time_len; i++)
        printf("-");
    puts("\n");
    // print_hash_table(&close_htable);
    // print_open_htable(&open_htable);

    puts("MEMORY");
    hash_node_t *tmp_node;
    size_t mem_open_htable = 0;
    size_t size = sizeof(hash_node_t);
    size_t mem_len = 6 + 15 + 15 + 15 + 5;

    for (size_t i = 0; i < mem_len; i++)
        printf("-");
    printf("\n|%6s|%15s|%15s|%15s|\n", "N", "Tree", "Close table", "Open table");
    for (size_t i = 0; i < mem_len; i++)
        printf("-");
    puts("");

    for (size_t i = 100; i <= AMOUNT_EL; i += 100)
    {
        for (size_t j = 0; j < i; j++)
        {
            // mem_open_htable += size;
            if (open_htable.array[j])
            {
                tmp_node = open_htable.array[j];
                while (tmp_node->node != NULL)
                {
                    tmp_node = tmp_node->node;
                    mem_open_htable += size;
                }
            }
        }
        printf("|%6zu|%15zu|%15zu|%15zu|\n", i, i * sizeof(tree_node_t), \
                                                2 * i * sizeof(hash_node_t) + sizeof(hash_table_t), \
                                                i * sizeof(hash_node_t) + mem_open_htable + sizeof(hash_table_t));
    }
    for (size_t i = 0; i < mem_len; i++)
        printf("-");
    puts("");
    return 0;
}
