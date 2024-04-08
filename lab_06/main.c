#include <stdio.h>
#include "func.h"

#define FILE_DOT "graph.gv"
#define FILE_PNG "graph.png"
#define TASK "\
\nВвести значения переменных: от A до I. Построить и вывести на экран бинарное\
\nдерево следующего выражения: A + (B * (C + (D * (E + F) - (G - H)) + I)). Написать процедуры\
\nпостфиксного, инфиксного и префиксного обхода дерева и вывести соответствующие выражения на экран.\
\nПодсчитать результат. Используя «польскую» запись, ввести данное выражение в стек.\
\nСравнить время вычисления выражения с использованием дерева и стека."

#define MENU "\
\nКомманды: \
\n1 - Ввести значения переменных: от A до I\
\n2 - Вывести бинарное дерево выражения A + (B * (C + (D * (E + F) - (G - H)) + I))\
\n3 - Вывести выражение (префиксный обход)\
\n4 - Вывести выражение (инфиксный обход)\
\n5 - Вывести выражение (постфиксный обход)\
\n6 - Вычислить значение выражения\
\n7 - Сравнить время вычисления выражения с использованием дерева и стека\
\n0 - Завершить работу программы\n"

int main(void)
{    
    size_t flag_fill = 0;
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
        while ((fscanf(stdin, "%d", &command) != 1 || command < 0 || command > 7)) 
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
                    export_to_dot(f, "MyGraph", &tree.sum_1);
                    fclose(f);
                    system("dot -Tpng "FILE_DOT" -o graph.png");
                    // system("gthumb "FILE_PNG);
                    printf("Выполнено\n");
                }
                break;
            case 3:
                apply_pre(&tree.sum_1, print_name_node, NULL);
                puts("");
                break;
            case 4:
                apply_in(&tree.sum_1, print_name_node, NULL);
                puts("");
                break;
            case 5:
                apply_post(&tree.sum_1, print_name_node, NULL);
                puts("");
                break;
            case 6:
                if (!flag_fill)
                {
                    printf("Ошибка, дерево не заполнено (выполните пункт 1 из меню)\n");
                    break;
                }
                printf("Результат вычисления выражения: %d\n", evaluate_postfix_expression(&tree.sum_1));
                break;
            case 7:
                if ((rc = cmp_tree_vs_stack(tree)))
                    printf("Возникла ошибка при вычислениях, перепроверьте данные (rc: %d)\n", rc);
                break;
        }
    }
    
    return 0;
}
