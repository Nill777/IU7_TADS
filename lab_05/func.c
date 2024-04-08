#include "func.h"
#define COUNT_TESTS 100

unsigned long long cur_mks_gettimeofday(void)
{
	struct timeval timeval;
	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000000 + timeval.tv_usec);
}

double get_time(const double min_time, const double max_time)
{
    double rnd = (double)rand() / (double)RAND_MAX;
    return (max_time - min_time) * rnd + min_time;
}

void clean_stdin(void)
{
    char c;
    do
        c = getchar();
    while (c != '\n');
}

int alloc_node(node_t **node)
{
    node_t *tmp;
    tmp = calloc(1, sizeof(node_t));
    if (tmp == NULL)
        return 1;
    *node = tmp;
    (*node)->next = NULL;
    return 0;
}

void free_list(node_t *list)
{
    node_t *prev = list;
    node_t *next = NULL;
    if (list != NULL)
        while ((next = prev->next) != NULL)
        {
            free(prev);
            prev = next;
        }
}

int pop_arr(queue_array_t *a, item_t *el)
{
    item_t tmp = {0, 0, 0.0, 0.0};
    if (a->size == 0)
        return 1;
    *el = a->arr[a->size - 1];
    for (size_t i = 0; i < a->size - 1; i++)
        a->arr[i] = a->arr[i + 1];
    a->arr[a->size - 1] = tmp;
    a->size--;
    return 0;
}

int push_arr(queue_array_t *a, item_t new_el)
{
    if (a->size >= MAX_SIZE)
        return 1;
    a->arr[a->size - 1] = new_el;
    a->size++;
    return 0;
}

// from head
int pop_list(queue_list_t *a, node_t *el)
{
    node_t *tmp;
    if (a->len == 0)
        return 1;
    if (a->head == NULL && a->tail == NULL)
        return 2;
    *el = *a->head;

    tmp = a->head;
    if (a->head == a->tail)
    {
        a->head = NULL;
        a->tail = NULL;
    }
    a->head = a->head->next;

    free(tmp);
    return 0;
}

// int push_stack_list(node_t **list, node_t **pl, int el)
// {
//     node_t *tmp_new_node = NULL;
//     if (*list == NULL || *pl == NULL)
//     {
//         if (create_node(list))
//             return 1;
//         *pl = *list;
//         (*pl)->val = el;
//     }
//     else
//     {
//         if (create_node(&tmp_new_node))
//             return 2;
//         (*pl)->next = tmp_new_node;
//         tmp_new_node->val = el;
//         *pl = tmp_new_node;
//     }
//     return 0;
// }

// from tail
int push_list(queue_list_t *a, node_t new_el, size_t print_flag)
{
    node_t *tmp_new_node = NULL;
    if (a->len >= MAX_SIZE)
        return 1;

    if (alloc_node(&tmp_new_node))
        return 3;
    *tmp_new_node = new_el;

    if (a->head == NULL)
    {
        a->head = tmp_new_node;
        a->tail = tmp_new_node;
    }
    else
    {
        a->tail->next = tmp_new_node;
        a->tail = tmp_new_node;
        if (print_flag)
            printf("%p\n", (void *) tmp_new_node);
    }
    a->len++;
    return 0;
}

// deplicate
void init_arr(queue_array_t *a)
{
    item_t tmp = {0, 0, 0.0, 0.0};
    for (size_t i = 0; i < MAX_SIZE; i++)
        a->arr[i] = tmp;
    a->size = 0;
    a->pin = a->arr;
    a->pout = a->pout;
}
// time ?
void gen_array(queue_array_t *a, size_t asize, size_t priority_queue)
{
    item_t tmp;
    double time = 0;
    a->size = 0;
    for (size_t i = 0; i < asize; i++)
    {
        tmp.number = i;
        tmp.priority_queue = priority_queue;
        tmp.time_in = time + get_time(a->t_in_min, a->t_in_max);
        // if (i <= 10)    printf("time %lf\n", tmp.time_in);
        tmp.time_proc = get_time(a->t_proc_min, a->t_proc_max);
        time = tmp.time_in;
        push_arr(a, tmp);
    }
}

void gen_list(queue_list_t *a, size_t asize, size_t priority_queue, size_t print_flag)
{
    item_t tmp = {0, 0, 0.0, 0.0};
    node_t tmp_node;
    double time = 0;
    a->len = 0;
    for (size_t i = 0; i < asize; i++)
    {
        tmp.number = i;
        tmp.priority_queue = priority_queue;
        tmp.time_in = time + get_time(a->t_in_min, a->t_in_max);
        // if (i <= 10)    printf("timelist %lf\n", tmp.time_in);
        tmp.time_proc = get_time(a->t_proc_min, a->t_proc_max);
        // if (i <= 10)    printf("timeproc %lf\n", tmp.time_proc);
        time = tmp.time_in;
        tmp_node.val = tmp;
        tmp_node.next = NULL;
        push_list(a, tmp_node, print_flag);
    }
}

int len_queue_array(queue_array_t *a, double cur_time)
{
    size_t count = 0;
    for (size_t i = 0; i < a->size && a->arr[i].time_in < cur_time; i++, count++);
    return count;
}

void gen_arr_el(queue_array_t *a, size_t priority_queue, int *number)
{ 
    a->el.number = *number;
    a->el.priority_queue = priority_queue;
    a->el.time_in = get_time(a->t_in_min, a->t_in_max);
    a->el.time_proc = get_time(a->t_proc_min, a->t_proc_max);
    (*number)++;
}

int process_array(queue_array_t *a, queue_array_t *b)
{
    double EPS = 0.0000001;
    int count_1 = 0;
    int count_2 = 0;
    int cur_len_q1 = 0;
    int sum_len_q1 = 0;
    // int sum_len_q2 = 0;

    // init_array(a);
    // init_array(b);
    // double time_1 = 0;
    // double time_2 = 0;
    // gen_array(a, MAX_SIZE, 1);
    // gen_array(b, MAX_SIZE, 2);

    // double tmp_time_1 = a->arr[0].time_in;
    // double tmp_time_2 = b->arr[0].time_in;

    // double cur_time_1 = 0;
    // double cur_time_2 = 0;

    // double prev_time_1 = 0;
    // double prev_time_2 = 0;

    double time_in_1 = 0;
    // double time_in_2 = 0;

    double time_proc_1 = 0;
    // double time_proc_2 = 0;

    item_t tmp;
    // int cur_priority = 0;
    // (void) cur_priority;
    // int count = 0;
    double lost_time = 0;
    int print_flag = 0;
    // int go_home = 0;

    int first = 1;
    // printf("first%d %lf %lf\n", a->arr[0].number, a->arr[0].time_in, a->arr[0].time_proc);
    printf("------------------------------------------------\n");
    printf("Начало моделирования\n");
    printf("------------------------------------------------\n");
    while (count_1 < LEN)
    {
        sum_len_q1 += cur_len_q1;
        // if (count < 20) printf("%lf\n", lost_time);
        // sum_len_q1 += len_queue_array(a, cur_time);
        // sum_len_q2 += len_queue_array(b, cur_time);

        if (!((count_1 + 1) % 100) && count_1 != 0 && print_flag != count_1)
        {
            print_flag = count_1;
            printf("Текущее время моделирования: %.2lf\n", time_in_1);
            printf("Обработано заявок 1-го типа: %d\n", count_1 + 1);
            // printf("Текущая длина 1-ой очереди: %d\n", len_queue_array(a, cur_time));
            printf("Средняя длина 1-ой очереди: %.2lf\n", (double) sum_len_q1 / count_1);
            printf("Обработано заявок 2-го типа: %d\n", count_2);
            // printf("Текущая длина 2-ой очереди: %d\n", len_queue_array(b, cur_time) + go_home);
            // printf("Средняя длина 2-ой очереди: %.2lf\n", (double) (sum_len_q2 + go_home) / count_2);
            printf("Время простоя: %.2lf\n", lost_time);
            // printf("Среднее время обработки заявок: %.2lf\n", time_in_1 / count);
            printf("------------------------------------------------\n");
        }
        // a
        double delta_time = 0;
        gen_arr_el(a, 1, &count_1);
        if (first)
        {
            time_in_1 = a->el.time_in;
            time_proc_1 = a->el.time_proc;
            first = 0;
            continue;
        }

        if (time_in_1 + time_proc_1 > time_in_1 + a->el.time_in + a->el.time_proc)
        {
            cur_len_q1 += 1;
            push_arr(a, a->el);
        }
        else if ((time_in_1 + a->el.time_in + a->el.time_proc) - EPS < (time_in_1 + time_proc_1) && (time_in_1 + time_proc_1) < (time_in_1 + a->el.time_in + a->el.time_proc) + EPS)
        {
            ;
        }
        else if (time_in_1 + time_proc_1 < time_in_1 + a->el.time_in + a->el.time_proc)
        {
            int del_els = 0;
            while (a->size != 0 && a->arr[0].time_proc < a->el.time_in - time_proc_1 - delta_time)
            {
                del_els++;
                delta_time += a->arr[0].time_proc;
                pop_arr(a, &tmp);
            }
            cur_len_q1 -= del_els;
        }
        time_in_1 += a->el.time_in;
        
        // while () 
        // prev_time_1 = a->el.time_in + a->el.time_proc;
        // cur_time_1 = 
        // sum_len_q1++;
        // size_t flag_lost = 1;
        // while (cur_time_2 < cur_time_1 + a->el.time_in)
        // {
        //     prev_time_2 = cur_time_2;
        //     gen_arr_el(b, 2, &count_2);
        //     cur_time_2 += b->el.time_proc;
        //     sum_len_q2++;
        // }
        // cur_time_2 = prev_time_2;
        // lost_time += cur_time_1 + a->el.time_proc;


        // if (a->arr[0].time_in <= cur_time)
        //     {
        //         item_t tmp;
        //         count++;
        //         cur_time += a->arr[0].time_proc;
        //         count_1++;
        //         pop_arr(a, &tmp);
        //         cur_priority = 1;
        //     }
        // else if (b->arr[0].time_in <= cur_time)
        //     if (cur_time + b->arr[0].time_proc >= a->arr[0].time_in)
        //     {
        //         item_t tmp;
        //         count++;
        //         lost_time += a->arr[0].time_in - cur_time;
        //         cur_time = a->arr[0].time_in + a->arr[0].time_proc;
        //         count_1++;
        //         pop_arr(a, &tmp);
        //         cur_priority = 1;
        //         // go_home++;
        //     }
        //     else
        //     {
        //         item_t tmp;
        //         count++;
        //         cur_time += b->arr[0].time_proc;
        //         count_2++;
        //         pop_arr(b, &tmp);
        //         cur_priority = 2;
        //         go_home++;
        //     }
        // else
        //     if (cur_time + b->arr[0].time_proc >= a->arr[0].time_in)
        //     {
        //         item_t tmp;
        //         count++;
        //         cur_time = a->arr[0].time_in + a->arr[0].time_proc;
        //         count_1++;
        //         pop_arr(a, &tmp);
        //         cur_priority = 1;
        //     }
        //     else
        //     {
        //         item_t tmp;
        //         count++;
        //         lost_time += b->arr[0].time_in - cur_time;
        //         cur_time = b->arr[0].time_in + b->arr[0].time_proc;
        //         count_2++;
        //         pop_arr(b, &tmp);
        //         cur_priority = 2;
        //     }
    }

    printf("Итоговые результаты (массив)\n");
	printf("Общее время моделирования: %.2lf\n", time_in_1);
	printf("Время простоя: %.2lf\n", lost_time);
	printf("Количество обработанных заявок 1-го типа: %d\n", count_1);
    printf("Количество обработанных заявок 2-го типа: %d\n", count_2);
    
    return 0;
}

int len_queue_list(queue_list_t *a, double cur_time)
{
    size_t count = 0;
    node_t *tmp = a->head;
    for (size_t i = 0; i < a->len && tmp->val.time_in < cur_time; i++, count++, tmp = tmp->next);
    return count;
}

void apply_list(queue_list_t *a)
{
    node_t *tmp = a->head;
    printf("+++\n");
    for (size_t i = 0; i < 10; i++)
    {
        printf("time %lf\n", tmp->val.time_in);
        tmp = tmp->next;
    }
    // while (tmp->next != NULL)
    // {
    //     printf("num=%d\n", tmp->val.number);
    //     tmp = tmp->next;
    // }
}

int process_list(queue_list_t *a, queue_list_t *b)
{
    int count_1 = 0;
    int count_2 = 0;
    int sum_len_q1 = 0;
    int sum_len_q2 = 0;
    
    a->head = NULL;
    a->tail = NULL;
    b->head = NULL;
    b->tail = NULL;

    gen_list(a, MAX_SIZE, 1, 0);
    // apply_list(a);
    // printf("metka");
    gen_list(b, MAX_SIZE, 2, 0);

    // double tmp_time_1 = a->arr[0].time_in;
    // double tmp_time_2 = b->arr[0].time_in;

    double cur_time = 0;
    int cur_priority = 0;
    (void) cur_priority;
    int count = 0;
    double lost_time = 0;
    int print_flag = 0;
    int go_home = 0;
    // printf("first%p %p %d %lf %lf\n", (void *) a->head, (void *) a->tail, a->head->val.number, a->head->val.time_in, a->head->val.time_proc);
    // printf("second%p %p %d %lf %lf\n", (void *) a->head, (void *) a->tail, a->head->next->val.number, a->head->next->val.time_in, a->head->next->val.time_proc);
    printf("------------------------------------------------\n");
    printf("Начало моделирования\n");
    printf("------------------------------------------------\n");
    while (count_1 < LEN)
    {
        // printf("count");
        // if (count < 20) printf("%lf\n", lost_time);
        sum_len_q1 += len_queue_list(a, cur_time);
        sum_len_q2 += len_queue_list(b, cur_time);

        if (!((count_1 + 1) % 100) && count_1 != 0 && print_flag != count_1)
        {
            print_flag = count_1;
            printf("Текущее время моделирования: %.2lf\n", cur_time);
            printf("Обработано заявок 1-го типа: %d\n", count_1 + 1);
            printf("Текущая длина 1-ой очереди: %d\n", len_queue_list(a, cur_time));
            printf("Средняя длина 1-ой очереди: %.2lf\n", (double) sum_len_q1 / count_1);
            printf("Обработано заявок 2-го типа: %d\n", count_2);
            printf("Текущая длина 2-ой очереди: %d\n", len_queue_list(b, cur_time) + go_home);
            printf("Средняя длина 2-ой очереди: %.2lf\n", (double) (sum_len_q2 + go_home) / count_1);
            printf("Время простоя: %.2lf\n", lost_time);
            printf("Среднее время обработки заявок: %.2lf\n", cur_time / count);
            printf("------------------------------------------------\n");
        }
        // a
        if (a->head->val.time_in <= cur_time)
            {
                node_t tmp;
                count++;
                cur_time += a->head->val.time_proc;
                count_1++;
                pop_list(a, &tmp);
                cur_priority = 1;
            }
        else if (b->head->val.time_in <= cur_time)
            if (cur_time + b->head->val.time_proc >= a->head->val.time_in)
            {
                node_t tmp;
                count++;
                lost_time += a->head->val.time_in - cur_time;
                cur_time = a->head->val.time_in + a->head->val.time_proc;
                count_1++;
                pop_list(a, &tmp);
                cur_priority = 1;
                // go_home++;
            }
            else
            {
                node_t tmp;
                count++;
                cur_time += b->head->val.time_proc;
                count_2++;
                pop_list(b, &tmp);
                cur_priority = 2;
                go_home++;
            }
        else
        {
            // puts("*");
            if (cur_time + b->head->val.time_proc >= a->head->val.time_in)
            {
                node_t tmp;
                count++;
                cur_time = a->head->val.time_in + a->head->val.time_proc;
                count_1++;
                // puts("#");
                pop_list(a, &tmp);
                // puts("@");
                cur_priority = 1;
            }
            else
            {
                node_t tmp;
                count++;
                lost_time += b->head->val.time_in - cur_time;
                cur_time = b->head->val.time_in + b->head->val.time_proc;
                count_2++;
                // puts("$");
                // printf("b %p %p %d %lf %lf\n", (void *) b->head, (void *) b->tail, b->head->val.number, b->head->val.time_in, b->head->val.time_proc);
                pop_list(b, &tmp);
                // puts("&");
                cur_priority = 2;
            }
        }
    }

    printf("Итоговые результаты (список)\n");
	printf("Общее время моделирования: %.2lf\n", cur_time);
	printf("Время простоя: %.2lf\n", lost_time);
	printf("Количество обработанных заявок 1-го типа: %d\n", count_1);
    printf("Количество обработанных заявок 2-го типа: %d\n", count_2);
    
    return 0;
}

int input_times(queue_array_t *a, queue_array_t *b, queue_list_t *c, queue_list_t *d)
{
    double t1_min, t1_max,
           t2_min, t2_max,
           t3_min, t3_max,
           t4_min, t4_max; 

    puts("Введите минимумы(через пробел) T1, T2, T3, T4:");
    if (scanf("%lf %lf %lf %lf", &t1_min, &t2_min, &t3_min, &t4_min) != 4 || 
            t1_min < 0 ||
            t2_min < 0 ||
            t3_min < 0 ||
            t4_min < 0)
        return 1;
    puts("Введите максимумы(через пробел) T1, T2, T3, T4:");
    if (scanf("%lf %lf %lf %lf", &t1_max, &t2_max, &t3_max, &t4_max) != 4 || 
            t1_max < 0 || t1_max < t1_min ||
            t2_max < 0 || t2_max < t2_min ||
            t3_max < 0 || t3_max < t3_min ||
            t4_max < 0 || t4_max < t4_min)
        return 2;

    a->t_in_max = c->t_in_max = t1_max;
    a->t_in_min = c->t_in_min = t1_min;
    a->t_proc_max = c->t_proc_max = t3_max;
    a->t_proc_min = c->t_proc_min = t3_min;

    b->t_in_max = d->t_in_max = t2_max;
    b->t_in_min = d->t_in_min = t2_min;
    b->t_proc_max = d->t_proc_max = t4_max;
    b->t_proc_min = d->t_proc_min = t4_min;

    printf("Новые значения:\nT1 %.0lf-%.0lf;\nT2 %.0lf-%.0lf;\nT3 %.0lf-%.0lf;\nT4 %.0lf-%.0lf;\n",
                t1_min, t1_max,
                t2_min, t2_max,
                t3_min, t3_max,
                t4_min, t4_max);
    return 0;
}

void print_addresses(void)
{
    queue_list_t a = {NULL, NULL, 0, 0.0, 0.0, 0.0, 0.0};
    gen_list(&a, LEN, 1, 1);
}
