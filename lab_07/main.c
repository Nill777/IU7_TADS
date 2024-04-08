#include <stdio.h>
#include "func.h"

#define FILE_DOT "graph.gv"
#define FILE_PNG "graph.png"
#define FILE_BST_DOT "graph_BST.gv"
#define FILE_BST_PNG "graph_BST.png"
#define TASK "\
\nИспользуя предыдущую программу (задача №6), построить дерево,\
\nнапример, для следующего выражения: 9+(8*(7+(6*(5+4)-(3-2))+1)). При\
\nпостфиксном обходе дерева, вычислить значение каждого узла и результат\
\nзаписать в его вершину. Получить массив, используя инфиксный обход\
\nполученного дерева. Построить для этих данных дерево двоичного поиска\
\n(ДДП), сбалансировать его. Построить хеш-таблицу для значений этого\
\nмассива. Осуществить поиск указанного значения. Сравнить время поиска,\
\nобъем памяти и количество сравнений при использовании ДДП,\
\nсбалансированных деревьев и хеш-таблиц."

#define MENU "\
\nКомманды: \
\n1 - Ввести значения переменных: от A до I\
\n2 - Вывести бинарное дерево выражения A + (B * (C + (D * (E + F) - (G - H)) + I))\
\n3 - Вычислить значение каждого узла и результат записать в его вершину\
\n4 - Построить сбалансированное дерево двоичного поиска\
\n5 - Сформировать хеш-таблицы\
\n6 - Вывести хеш-таблицы\
\n7 - Поиск в дереве двоичного поиска\
\n8 - Поиск в хеш-таблице (закрытого типа)\
\n9 - Поиск в хеш-таблице (открытого типа)\
\n10 - Сравнить поиск в дереве двоичного поиска и в хеш-таблицах\
\n0 - Завершить работу программы\n"

int main(void)
{    
    size_t flag_fill = 0;
    size_t flag_fill_tree = 0;
    size_t flag_fill_table = 0;
    tree_node_t *BST_tree = NULL;
    hash_table_t table_1;
    hash_table_t table_2;
    struct val_nodes tree;
    // printf("pm%p\n", (void *) &tree);
    tree.sum_1.name = "+_1";
    tree.sum_1.parent = NULL;
    tree.sum_1.left = &tree.A;
    tree.sum_1.right = &tree.mul_1;

    tree.A.name = "A";
    tree.A.parent = &tree.sum_1;
    tree.A.left = NULL;
    tree.A.right = NULL;

    tree.mul_1.name = "*_1";
    tree.mul_1.parent = &tree.sum_1;
    tree.mul_1.left = &tree.B;
    tree.mul_1.right = &tree.sum_2;

    tree.B.name = "B";
    tree.B.parent = &tree.mul_1;
    tree.B.left = NULL;
    tree.B.right = NULL;
    
    tree.sum_2.name = "+_2";
    tree.sum_2.parent = &tree.mul_1;
    tree.sum_2.left = &tree.C;
    tree.sum_2.right = &tree.sum_3;

    tree.C.name = "C";
    tree.C.parent = &tree.sum_2;
    tree.C.left = NULL;
    tree.C.right = NULL;

    tree.sum_3.name = "+_3";
    tree.sum_3.parent = &tree.sum_2;
    tree.sum_3.left = &tree.sub_1;
    tree.sum_3.right = &tree.I;

    tree.sub_1.name = "-_1";
    tree.sub_1.parent = &tree.sum_3;
    tree.sub_1.left = &tree.mul_2;
    tree.sub_1.right = &tree.sub_2;

    tree.I.name = "I";
    tree.I.parent = &tree.sum_3;
    tree.I.left = NULL;
    tree.I.right = NULL;

    tree.mul_2.name = "*_2";
    tree.mul_2.parent = &tree.sub_1;
    tree.mul_2.left = &tree.D;
    tree.mul_2.right = &tree.sum_4;

    tree.sub_2.name = "-_2";
    tree.sub_2.parent = &tree.sub_1;
    tree.sub_2.left = &tree.G;
    tree.sub_2.right = &tree.H;

    tree.D.name = "D";
    tree.D.parent = &tree.mul_2;
    tree.D.left = NULL;
    tree.D.right = NULL;

    tree.sum_4.name = "+_4";
    tree.sum_4.parent = &tree.mul_2;
    tree.sum_4.left = &tree.E;
    tree.sum_4.right = &tree.F;

    tree.G.name = "G";
    tree.G.parent = &tree.sub_2;
    tree.G.left = NULL;
    tree.G.right = NULL;

    tree.H.name = "H";
    tree.H.parent = &tree.sub_2;
    tree.H.left = NULL;
    tree.H.right = NULL;

    tree.E.name = "E";
    tree.E.parent = &tree.sum_4;
    tree.E.left = NULL;
    tree.E.right = NULL;

    tree.F.name = "F";
    tree.F.parent = &tree.sum_4;
    tree.F.left = NULL;
    tree.F.right = NULL;

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
                if ((rc = fill_tree(&tree)))
                {
                    clean_stdin();
                    printf("Ошибка ввода, перепроверьте данные и попробуйте снова\n");
                }
                else
                    flag_fill = 1;
                break;
            case 2:
                {
                    FILE *f = fopen(FILE_DOT, "w");
                    if (!f)
                    {
                        printf("Ошибка открытия файла "FILE_DOT", проверьте его наличие\n");
                        break;
                    }
                    export_to_dot(f, "MyGraph", &tree.sum_1, print_node_name);
                    fclose(f);
                    if (system("dot -Tpng "FILE_DOT" -o "FILE_PNG))
                    {
                        printf("Ошибка формирования файла "FILE_DOT", перепроверьте данные\n");
                        break;
                    }
                    // system("gthumb "FILE_PNG);
                    printf("Выполнено\n");
                }
                break;
            case 3:
                {
                    if (!flag_fill)
                    {
                        printf("Ошибка, дерево не заполнено (выполните пункт 1 из меню)\n");
                        break;
                    }
                    postfix_evaluation(&tree.sum_1);
                    FILE *f = fopen(FILE_DOT, "w");
                    if (!f)
                    {
                        printf("Ошибка открытия файла "FILE_DOT", проверьте его наличие\n");
                        break;
                    }
                    export_to_dot(f, "MyGraph", &tree.sum_1, print_node_val);
                    fclose(f);
                    if (system("dot -Tpng "FILE_DOT" -o "FILE_PNG))
                    {
                        printf("Ошибка формирования файла "FILE_DOT", перепроверьте данные\n");
                        break;
                    }
                    // system("gthumb "FILE_PNG);
                    printf("Выполнено\n");
                }
                break;
            // Получить массив, используя инфиксный обход
            // полученного дерева. Построить для этих данных дерево двоичного поиска
            // (ДДП), сбалансировать его.
            case 4:
                {
                    size_t asize = 17;
                    int a[asize];

                    if (!flag_fill)
                    {
                        printf("Ошибка, дерево не заполнено (выполните пункт 1 из меню)\n");
                        break;
                    }

                    postfix_evaluation(&tree.sum_1);
                    // puts("*");

                    // tree_node_t *node = NULL;
                    // tree_node_t *tmp = NULL;

                    // if (create_node(&node, 1))
                    //     puts("invalid_create");
                    // else
                    //     puts("valcreate");
                    // node->left = tmp;

                    // puts("*");
                    form_arr(&tree.sum_1, a);
                    // for (size_t i = 0; i < asize; i++)
                    //     printf("%d ", a[i]);

                    // puts("*");
                    if (!(BST_tree = balance_BST(a, asize)))
                    {
                        printf("Ошибка, не удалось сформировать BST\n");
                        break;
                    }
                    // puts("*");
                    // if (create_table(&table, asize))
                    // {
                    //     printf("Ошибка, не удалось сформировать хеш-таблицу\n");
                    //     break;
                    // }
                    // puts("*");
                    // fill_hash_table(&table, a, asize);
                    // puts("^");
                    // for (size_t i = 0; i < 2 * table.size; i++)
                    // {
                    //     printf("p %p, ", (void *) table.array[i]);
                    //     if (table.array[i])
                    //         printf("val %d\n", table.array[i]->value);
                    // }
                    // puts("^");
                    // puts("*");

                    FILE *f = fopen(FILE_BST_DOT, "w");
                    if (!f)
                    {
                        printf("Ошибка открытия файла "FILE_BST_DOT", проверьте его наличие\n");
                        break;
                    }
                    export_to_dot(f, "MyGraph", BST_tree, print_node_val);
                    fclose(f);
                    if (system("dot -Tpng "FILE_BST_DOT" -o "FILE_BST_PNG))
                    {
                        printf("Ошибка формирования файла "FILE_BST_PNG", перепроверьте данные\n");
                        break;
                    }
                    // system("gthumb "FILE_PNG);
                    flag_fill_tree = 1;
                    printf("Выполнено\n");
                }
                break;
            case 5:
                {
                    size_t asize = 17;
                    int a[asize];

                    if (!flag_fill)
                    {
                        printf("Ошибка, дерево не заполнено (выполните пункт 1 из меню)\n");
                        break;
                    }

                    postfix_evaluation(&tree.sum_1);
                    form_arr(&tree.sum_1, a);

                    if (create_table(&table_1, asize))
                    {
                        printf("Ошибка, не удалось сформировать хеш-таблицу\n");
                        break;
                    }
                    if (create_open_htable(&table_2, asize))
                    {
                        printf("Ошибка, не удалось сформировать хеш-таблицу\n");
                        break;
                    }

                    fill_hash_table(&table_1, a, asize);
                    fill_hash_table_open(&table_2, a, asize);
                    flag_fill_table = 1;
                    printf("Выполнено\n");
                }
                break;
            case 6:
                if (!flag_fill_table)
                {
                    printf("Ошибка, хеш-таблица не сформирована (выполните пункт 5 из меню)\n");
                    break;
                }
                print_hash_table(&table_1);
                print_open_htable(&table_2);
                break;
            case 7:
                {
                    tree_node_t *tmp;
                    int search_val;
                    if (!flag_fill_tree)
                    {
                        printf("Ошибка, дерево двоичного поиска не сформировано (выполните пункт 4 из меню)\n");
                        break;
                    }
                    printf("Введите искомое значение: ");
                    if (scanf("%d", &search_val) != 1)
                    {
                        printf("Ошибка ввода, перепроверьте данные и попробуйте снова\n");
                        break;
                    }
                    size_t cmp = 0;
                    tmp = search_from_tree(BST_tree, search_val, &cmp);
                    if (tmp)
                        printf("Элемент найден, его название: %s\n", tmp->name);
                    else
                        printf("Элемент не найден\n");
                }
                break;
            case 8:
                {
                    hash_node_t *tmp;
                    int search_val;
                    if (!flag_fill_table)
                    {
                        printf("Ошибка, хеш-таблица не сформирована (выполните пункт 5 из меню)\n");
                        break;
                    }
                    printf("Введите искомое значение: ");
                    if (scanf("%d", &search_val) != 1)
                    {
                        printf("Ошибка ввода, перепроверьте данные и попробуйте снова\n");
                        break;
                    }
                    // puts("^");
                    // for (size_t i = 0; i < table.size; i++)
                    // {
                    //     printf("i %zu, p %p, ", i, (void *) table.array[i]);
                    //     if (table.array[i])
                    //         printf("key %d, val %d\n", table.array[i]->key, table.array[i]->value);
                    // }
                    // puts("^");
                    size_t cmp = 0;
                    tmp = search_from_hash_table(&table_1, search_val, &cmp);
                    if (tmp)
                        printf("Элемент найден, его хеш: %d\n", tmp->key);
                    else
                        printf("Элемент не найден\n");
                }
                break;
            case 9:
                {
                    hash_node_t *tmp;
                    int search_val;
                    if (!flag_fill_table)
                    {
                        printf("Ошибка, хеш-таблица не сформирована (выполните пункт 5 из меню)\n");
                        break;
                    }
                    printf("Введите искомое значение: ");
                    if (scanf("%d", &search_val) != 1)
                    {
                        printf("Ошибка ввода, перепроверьте данные и попробуйте снова\n");
                        break;
                    }
                    // puts("^");
                    // for (size_t i = 0; i < table.size; i++)
                    // {
                    //     printf("i %zu, p %p, ", i, (void *) table.array[i]);
                    //     if (table.array[i])
                    //         printf("key %d, val %d\n", table.array[i]->key, table.array[i]->value);
                    // }
                    // puts("^");
                    size_t cmp = 0;
                    tmp = open_htable_search(&table_2, search_val, &cmp);
                    if (tmp)
                        printf("Элемент найден, его хеш: %d\n", tmp->key);
                    else
                        printf("Элемент не найден\n");
                }
                break;
            case 10:
                cmp_tree_vs_table();
                break;
        }
    }
    
    return 0;
}
