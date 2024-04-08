#include "func.h"
#define COUNT_TESTS 100

unsigned long long cur_mks_gettimeofday(void)
{
	struct timeval timeval;
	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000000 + timeval.tv_usec);
}

void clean_stdin(void)
{
    char c;
    do
        c = getchar();
    while (c != '\n');
}

int create_node(node_t **node)
{
    *node = calloc(1, sizeof(node_t));
    if (node == NULL)
        return 1;
    (*node)->next = NULL;
    return 0;
}

int pop_stack_arr(int *stack_arr, int **ps, int *el)
{
    if (stack_arr == *ps)
        return 1;
    (*ps)--;
    *el = **ps;
    return 0;
}

int push_stack_arr(int *stack_arr, int **ps, int el)
{
    if (stack_arr + MAX_LEN_ARR * sizeof(int) == *ps + sizeof(int))
        return 1;
    **ps = el;
    (*ps)++;
    return 0;
}

int pop_stack_list(node_t *list, node_t **pl, int *el)
{
    if (list == NULL || *pl == NULL)
        return 1;
    *el = (*pl)->val;
    node_t *prev = list;
    while (prev->next != *pl)
        prev = prev->next;
    *pl = prev;
    return 0;
}

int push_stack_list(node_t **list, node_t **pl, int el)
{
    node_t *tmp_new_node = NULL;
    if (*list == NULL || *pl == NULL)
    {
        if (create_node(list))
            return 1;
        *pl = *list;
        (*pl)->val = el;
    }
    else
    {
        if (create_node(&tmp_new_node))
            return 2;
        (*pl)->next = tmp_new_node;
        tmp_new_node->val = el;
        *pl = tmp_new_node;
    }
    return 0;
}

void free_list(node_t *list)
{
    node_t *prev = list;
    node_t *next = NULL;
    if (list == NULL)
        ;
    else
        while ((next = prev->next) != NULL)
        {
            free(prev);
            prev = next;
        }
}

int fscanf_exp(char *src, node_t **list, node_t **pl, int *stack_arr, int **ps, size_t print_flag)
{
    *ps = stack_arr;
    *list = NULL;
    *pl = NULL;
    FILE *file = fopen(src, "r");
    if (file == NULL)
    {
        puts("Ошибка открытия файла");
        return 1;
    }
    char tmp_sign, tmp;
    int tmp_el;
    if (fscanf(file, "%d", &tmp_el) != 1)
        return 2;
    if (push_stack_arr(stack_arr, ps, tmp_el))
        return 3;

    if (push_stack_list(list, pl, tmp_el))
        return 4;
    size_t count = 1;
    int rc;
    while (fscanf(file, "%c", &tmp) == 1 && tmp == ' ')
    {
        if (fscanf(file, "%c", &tmp_sign) != 1 || !(tmp_sign == '+' || tmp_sign == '-' || tmp_sign == '/' || tmp_sign == '*'))
            return 5;
        if (push_stack_arr(stack_arr, ps, tmp_sign))
            return 6;
        if ((rc = push_stack_list(list, pl, tmp_sign)))
            return 7;
        if (fscanf(file, "%c", &tmp) != 1 || tmp != ' ')
            return 8;
        if (fscanf(file, "%d", &tmp_el) != 1 || (tmp_el == 0 && tmp_sign == '/'))
            return 9;
        if (push_stack_arr(stack_arr, ps, tmp_el))
            return 10;

        if (push_stack_list(list, pl, tmp_el))
            return 11;
        count++;
    }
    fclose(file);

    if (print_flag)
        puts("Стеки заполнены автоматически");
    return 0;
}

int input_exp(node_t **list, node_t **pl, int *stack_arr, int **ps)
{
    int count;
    *ps = stack_arr;
    *list = NULL;
    *pl = NULL;
    puts("Введите количество операндов:");
    while (scanf("%d", &count) != 1 || count <= 0)
    {
        puts("Некорректное количество операндов");
        clean_stdin();
    }
    clean_stdin();

    // Ввод
    puts("Введите выражение, элементы должны быть разделены пробелами");
    char tmp_sign;
    int tmp_el;
    if (scanf("%d", &tmp_el) != 1)
        return 2;
    if (push_stack_arr(stack_arr, ps, tmp_el))
        return 3;
    if (push_stack_list(list, pl, tmp_el))
        return 4;
    for (int i = 0; i < count - 1 && getchar() == ' '; i++)
    {
        if (scanf("%c", &tmp_sign) != 1 || !(tmp_sign == '+' || tmp_sign == '-' || tmp_sign == '/' || tmp_sign == '*'))
            return 4;
        if (push_stack_arr(stack_arr, ps, tmp_sign))
            return 5;
        if (push_stack_list(list, pl, tmp_sign))
            return 7;

        if (getchar() != ' ')
            return 6;
        if (scanf("%d", &tmp_el) != 1 || (tmp_el == 0 && tmp_sign == '/'))
            return 7;
        if (push_stack_arr(stack_arr, ps, tmp_el))
            return 8;
        if (push_stack_list(list, pl, tmp_el))
            return 11;
    }
    if (getchar() == '\n')
        puts("Стеки заполнены");
    else
    {
        puts("Некорректное выражение");
        *ps = stack_arr;
        *list = NULL;
        *pl = NULL;
        clean_stdin();
    }
    return 0;
}

int print_stack_arr(int *stack_arr, int *ps, int i)
{
    int tmp_el;
    printf("Стек в виде массива\n");
    for (; stack_arr != ps; i++)
    {
        if (pop_stack_arr(stack_arr, &ps, &tmp_el))
            return 1;
        if (i % 2)
            printf("%d", tmp_el);
        else
            printf("%c", tmp_el);
    }
    puts("");
    return 0;
}

int print_stack_list(node_t *stack_list, node_t *pl, int i)
{
    int tmp_el;
    printf("Стек в виде списка\n");
    if (stack_list == NULL || pl == NULL)
    {
        puts("");
        return 0;
    }
    for (; stack_list != pl; i++)
    {
        if (pop_stack_list(stack_list, &pl, &tmp_el))
            return 1;
        if (i % 2)
            printf("%d", tmp_el);
        else
            printf("%c", tmp_el);
    }
    printf("%d", stack_list->val);
    puts("");
    return 0;
}

int calc_exp_arr(int *stack_arr, int *ps, size_t print_flag)
{
    int res;
    // 1: +
    // 2: -
    // 3: *
    // 4: /
    int operation;
    int tmp_stack[MAX_LEN_ARR];
    int *tmp_ps = tmp_stack;
    int tmp_el;
    if (stack_arr == ps)
    {
        puts("Стек пуст, невозможно вычислить значение выражения");
        return 1;
    }
    while (stack_arr != ps)
    {
        if (pop_stack_arr(stack_arr, &ps, &tmp_el))
            return 2;
        if (push_stack_arr(tmp_stack, &tmp_ps, tmp_el))
            return 3;
    }
    if (pop_stack_arr(tmp_stack, &tmp_ps, &tmp_el))
        return 4;
    res = tmp_el;
    for (size_t i = 2; tmp_stack != tmp_ps; i++)
    {
        if (pop_stack_arr(tmp_stack, &tmp_ps, &tmp_el))
            return 5;
        if (i % 2)
        {
            if (operation == 1)
                res += tmp_el;
            if (operation == 2)
                res -= tmp_el;
            if (operation == 3)
                res *= tmp_el;
            if (operation == 4)
                res /= tmp_el;
        }
        else
        {
            if (tmp_el == '+')
                operation = 1;
            if (tmp_el == '-')
                operation = 2;
            if (tmp_el == '*')
                operation = 3;
            if (tmp_el == '/')
                operation = 4;
        }
    }
    if (print_flag)
        printf("Значение выражения: %d\n", res);
    return 0;
}

int calc_exp_list(node_t *stack_list, node_t *pl, size_t print_flag)
{
    int res;
    // 1: +
    // 2: -
    // 3: *
    // 4: /
    int operation;
    node_t *tmp_stack = NULL;
    node_t *tmp_pl = tmp_stack;
    int tmp_el;

    if (stack_list == pl)
    {
        res = pl->val;
        goto print;
    }
    if (stack_list == NULL)
    {
        puts("Стек пуст, невозможно вычислить значение выражения");
        return 1;
    }
    while (stack_list != pl)
    {
        if (pop_stack_list(stack_list, &pl, &tmp_el))
            return 2;
        if (push_stack_list(&tmp_stack, &tmp_pl, tmp_el))
            return 3;
    }
    tmp_el = stack_list->val;
    if (push_stack_list(&tmp_stack, &tmp_pl, tmp_el))
        return 3;

    if (pop_stack_list(tmp_stack, &tmp_pl, &tmp_el))
        return 4;
    res = tmp_el;
    for (size_t i = 2; tmp_stack != tmp_pl; i++)
    {
        if (pop_stack_list(tmp_stack, &tmp_pl, &tmp_el))
            return 5;
        if (i % 2)
        {
            if (operation == 1)
                res += tmp_el;
            if (operation == 2)
                res -= tmp_el;
            if (operation == 3)
                res *= tmp_el;
            if (operation == 4)
                res /= tmp_el;
        }
        else
        {
            if (tmp_el == '+')
                operation = 1;
            if (tmp_el == '-')
                operation = 2;
            if (tmp_el == '*')
                operation = 3;
            if (tmp_el == '/')
                operation = 4;
        }
    }
    tmp_el = tmp_stack->val;
    if (operation == 1)
        res += tmp_el;
    if (operation == 2)
        res -= tmp_el;
    if (operation == 3)
        res *= tmp_el;
    if (operation == 4)
        res /= tmp_el;

print:
    if (print_flag)
        printf("Значение выражения: %d\n", res);
    return 0;
}

void efficency_table(void)
{
    char file[30];
    puts("Время указано в мкс, затраты памяти в байтах");
    puts("TIME");
    for (size_t i = 0; i < 5 + 15 + 15 + 4; i++)
        printf("-");
    printf("\n|%5s|%15s|%15s|\n", "N", "Stack array", "Stack list");
    for (size_t i = 0; i < 5 + 15 + 15 + 4; i++)
        printf("-");
    puts("");

    for (size_t i = 100; i <= 5000; i += 100)
    {
        unsigned long long start_time1;
        unsigned long long finish_time1;
        unsigned long long start_time2;
        unsigned long long finish_time2;
        
        unsigned long long avg_time1 = 0;
        unsigned long long avg_time2 = 0;
        for (size_t k = 0; k < COUNT_TESTS; k++)
        {
            int stack_arr[MAX_LEN_ARR];
            int *ps = stack_arr;
            node_t *stack_list = NULL;
            node_t *pl = stack_list;

            sprintf(file, "./data/test_%zu.txt", i);
            fscanf_exp(file, &stack_list, &pl, stack_arr, &ps, 0);
            start_time1 = cur_mks_gettimeofday();
            calc_exp_arr(stack_arr, ps, 0);
            finish_time1 = cur_mks_gettimeofday();
            start_time2 = cur_mks_gettimeofday();
            calc_exp_list(stack_list, pl, 0);
            finish_time2 = cur_mks_gettimeofday();

            avg_time1 += finish_time1 - start_time1;
            avg_time2 += finish_time2 - start_time2;
        }
        printf("|%5zu|%15llu|%15llu|\n", 2 * i - 1, avg_time1 / COUNT_TESTS, avg_time2 / COUNT_TESTS);
    }
    for (size_t i = 0; i < 5 + 15 + 15 + 4; i++)
        printf("-");
    puts("");

    puts("MEMORY");
    for (size_t i = 0; i < 5 + 15 + 15 + 4; i++)
        printf("-");
    printf("\n|%5s|%15s|%15s|\n", "N", "Stack array", "Stack list");
    for (size_t i = 0; i < 5 + 15 + 15 + 4; i++)
        printf("-");
    puts("");
    for (size_t i = 100; i <= 5000; i += 100)
        printf("|%5zu|%15lu|%15lu|\n", 2 * i - 1, MAX_LEN_ARR * sizeof(int), i * sizeof(node_t));
    for (size_t i = 0; i < 5 + 15 + 15 + 4; i++)
        printf("-");
    puts("");
}
