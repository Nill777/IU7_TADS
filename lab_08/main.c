#include <stdio.h>
#include "graph.h"

#define FILE_SRC "graph.txt"
#define FILE_DOT "graph.gv"
#define FILE_PNG "graph.png"

#define MENU "\
\nКомманды: \
\n1 - Считать граф из файла\
\n2 - Вывести граф\
\n3 - Найти самый длинный простой путь в графе\
\n4 - Проверить связность графа\
\n5 - Построить остовое дерево минимальной стоимости\
\n6 - Вывести таблицу эффективности\
\n0 - Завершить работу программы\n"

void clean_stdin(void)
{
    char c;
    while ((c = getchar()) != '\n');
}

int main(void)
{
    graph_t a = {.size = 0};
    int command = -1;
    int rc;
    while (command != 0)
    {
        puts(MENU);
        while ((fscanf(stdin, "%d", &command) != 1 || command < 0 || command > 6)) 
        {
            puts("Некорректная комманда");
            puts("Введите команду:");
            clean_stdin();
        }
        clean_stdin();
        switch (command)
        {
            case 1:
                if ((rc = read_graph_from_file(&a, FILE_SRC)))
                {
                    printf("Ошибка ввода, перепроверьте данные и попробуйте снова\n");
                    break;
                }
                // for (size_t i = 0; i < a.size; i++)
                // {
                //     for (size_t j = 0; j < a.size; j++)
                //     {
                //         printf("%d ", a.matrix[i][j]);

                //     }
                //     puts("");
                // }
                printf("Выполнено\n");
                break;
            case 2:
                {
                    if (!a.size)
                    {
                        printf("Ошибка, граф не заполнен (выполните пункт 1 из меню)\n");
                        break;
                    }
                    FILE *f = fopen(FILE_DOT, "w");
                    if (!f)
                    {
                        printf("Ошибка открытия файла "FILE_DOT", проверьте его наличие\n");
                        break;
                    }
                    export_to_dot(f, "MyGraph", &a);
                    fclose(f);
                    if (system("dot -Tpng "FILE_DOT" -o "FILE_PNG))
                    {
                        printf("Ошибка формирования файла "FILE_DOT", перепроверьте данные\n");
                        break;
                    }
                    printf("Выполнено\n");
                }
                break;
            case 3:
                {
                    simple_path_t info;
                    if (!a.size)
                    {
                        printf("Ошибка, граф не заполнен (выполните пункт 1 из меню)\n");
                        break;
                    }
                    find_max_simple_path(&a, &info);
                    puts("Самый длинный простой путь в графе:");
                    print_path(&info);
                    break;
                }
            case 4:
                if (!a.size)
                {
                    printf("Ошибка, граф не заполнен (выполните пункт 1 из меню)\n");
                    break;
                }
                if ((rc = is_graph_connected(&a)) == 1)
                    puts("Граф связный");
                else if (rc == 0)
                    puts("Граф не связный");
                break;
            case 5:
                if (!a.size)
                {
                    printf("Ошибка, граф не заполнен (выполните пункт 1 из меню)\n");
                    break;
                }
                if ((rc = minimum_spanning_tree(&a)))
                    printf("Ошибка, граф не заполнен (выполните пункт 1 из меню)\n");
                break;
            case 6:
                table_efficiency();
                break;
        }
    }
    return 0;
}