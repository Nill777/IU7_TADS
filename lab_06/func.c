#include "func.h"
#define COUNT_TESTS 100
#define SIZE 17

unsigned long long cur_ns_gettimeofday(void)
{
	struct timeval timeval;
	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000000000 + timeval.tv_usec * 1000);
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

void to_dot(tree_node_t *tree, void *param)
{
    FILE *f = param;
    if (tree->left)
        fprintf(f, "\"%s\" -> \"%s\";\n", tree->name, tree->left->name);
    if (tree->right)
        fprintf(f, "\"%s\" -> \"%s\";\n", tree->name, tree->right->name);
}

void print_node(tree_node_t *tree, void *param)
{
    FILE *f = param;
    fprintf(f, "\"%s\" [label=\"%c\"];\n", tree->name, tree->name[0]);
}

void export_to_dot(FILE *f, const char *tree_name, struct tree_node *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);
    apply_pre(tree, print_node, f);
    apply_pre(tree, to_dot, f);
    fprintf(f, "}\n");
}

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
