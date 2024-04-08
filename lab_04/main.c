#include <stdio.h>
#include "func.h"

#define FILE_IN "file_in.txt"
#define TASK "\
\nВвести арифметическое выражение типа: число|знак| … число|знак|число.\
\nВычислить значение выражения. (Приоритетность операций необязательна)"

#define MENU "\
\nИсходные данные хранятся в файле file_in.txt. Программа не будет работать корректно,\
\nесли исходный файл не существует.\
\nСодержимое исходного файла неопределено при принудительном завершении\
\nКомманды: \
\n1 - Заполнить стек используя данные из файла\
\n2 - Заполнить стек вручную\
\n3 - Вывести исходный стек\
\n4 - Вычислить выражение (стек - статический массив)\
\n5 - Вычислить выражение (стек - список)\
\n6 - push (стек - статический массив)\
\n7 - pop (стек - статический массив)\
\n8 - push (стек - список)\
\n9 - pop (стек - список)\
\n10 - Получения таблицы производительности\
\n0 - Завершить работу программы\n"

int main()
{    
    int stack_arr[MAX_LEN_ARR];
    int *ps = stack_arr;

    node_t *stack_list = NULL;
    node_t *pl = stack_list;

    char oper;
    int el;
    int f_print_arr = 1;
    int f_print_list = 1;
    int command = -1;
    int rc;
    puts(TASK);
    while (command != 0)
    {
        puts(MENU);
        while ((fscanf(stdin, "%d", &command) != 1 || command < 0 || command > 10)) 
        {
            puts("Некорректная комманда");
            puts("Введите команду:");
            clean_stdin();
        }
        clean_stdin();
        switch (command)
        {
            case 1:
                if ((rc = fscanf_exp(FILE_IN, &stack_list, &pl, stack_arr, &ps, 1)))
                    printf("Ошибка автоматического ввода выражения, перепроверьте исходные данные %d\n", rc);
                break;
            case 2:
                if (input_exp(&stack_list, &pl, stack_arr, &ps))
                    puts("Ошибка ввода выражения, попробуйте ещё раз");
                break;
            case 3:
                if (print_stack_arr(stack_arr, ps, f_print_arr) || print_stack_list(stack_list, pl, f_print_list))
                    puts("Ошибка, печатать нечего, перепроверьте корректность данных");
                break;
            case 4:
                if (f_print_arr == 2)
                {
                    puts("Некорректное выражение, перепроверьте данные");
                    break;
                }
                if (calc_exp_arr(stack_arr, ps, 1))
                    puts("Ошибка вычисления выражения, перепроверьте данные");
                break;
            case 5:
                if (f_print_list == 2)
                {
                    puts("Некорректное выражение, перепроверьте данные");
                    break;
                }
                if (calc_exp_list(stack_list, pl, 1))
                    puts("Ошибка вычисления выражения, перепроверьте данные");
                break;
            case 6:
                if (f_print_list == 2)
                {
                    puts("Некорректное выражение, перепроверьте данные");
                    break;
                }
                puts("Введите операцию для добавления в стек (массив):");
                while (scanf("%c", &oper) != 1 || !(oper == '+' || oper == '-' || oper == '/' || oper == '*'))
                {
                    puts("Некорректная операция");
                    clean_stdin();
                }
                clean_stdin();

                puts("Введите элемент для добавления в стек (массив):");
                while (scanf("%d", &el) != 1)
                {
                    puts("Некорректный элемент");
                    clean_stdin();
                }
                clean_stdin();
                rc = 0;
                if ((rc = push_stack_arr(stack_arr, &ps, oper)))
                    rc = 1;
                if ((rc = push_stack_arr(stack_arr, &ps, el)))
                    rc = 1;
                if (rc)
                    puts("Ошибка записи, перепроверьте данные");
                puts("Выполнено");
                break;
            case 7:
                if (pop_stack_arr(stack_arr, &ps, &el))
                {
                    puts("Стек пуст, перепроверьте данные");
                    break;
                }
                if (f_print_arr == 1)
                    f_print_arr = 2;
                else
                    f_print_arr = 1;
                puts("Выполнено");
                break;
            case 8:
                if (f_print_list == 2)
                {
                    puts("Некорректное выражение, перепроверьте данные");
                    break;
                }
                puts("Введите операцию для добавления в стек (лист):");
                while (scanf("%c", &oper) != 1 || !(oper == '+' || oper == '-' || oper == '/' || oper == '*'))
                {
                    puts("Некорректная операция");
                    clean_stdin();
                }
                clean_stdin();

                puts("Введите элемент для добавления в стек (лист):");
                while (scanf("%d", &el) != 1)
                {
                    puts("Некорректный элемент");
                    clean_stdin();
                }
                clean_stdin();
                rc = 0;
                if ((rc = push_stack_list(&stack_list, &pl, oper)))
                    rc = 1;
                if ((rc = push_stack_list(&stack_list, &pl, el)))
                    rc = 1;
                if (rc)
                {
                    puts("Ошибка записи, перепроверьте данные");
                    break;
                }
                puts("Выполнено");
                break;
            case 9:
                if (stack_list == pl)
                    pl = NULL;
                else
                    if (pop_stack_list(stack_list, &pl, &el))
                    {
                        puts("Стек пуст, перепроверьте данные");
                        break;
                    }
                if (f_print_list == 1)
                    f_print_list = 2;
                else
                    f_print_list = 1;
                puts("Выполнено");
                break;
            case 10:
                efficency_table();
                break;
        }
    }
    free_list(stack_list); 
    return 0;
}
