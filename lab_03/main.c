#include <stdio.h>
#include "func.h"

#define FILE_IN "file_in.txt"
#define TASK "\
\nРазреженная (содержащая много нулей) матрица хранится в форме 3-х объектов:\
\n- вектор A содержит значения ненулевых элементов;\
\n- вектор IA содержит номера строк для элементов вектора A;\
\n- вектор JA, в элементе Nk которого находится номер компонент\
\nв A и IA, с которых начинается описание столбца Nk матрицы A.\
\n1. Смоделировать операцию сложения двух матриц, хранящихся в этой форме,\
\nс получением результата в той же форме.\
\n2. Произвести операцию сложения, применяя стандартный алгоритм работы с\
\nматрицами.\
\n3. Сравнить время выполнения операций и объем памяти при использовании\
\nэтих 2-х алгоритмов при различном проценте заполнения матриц."

#define MENU "\
\nИсходные данные хранятся в файле file_in.txt. Программа не будет работать корректно, если исходный файл не существует.\
\nСодержимое исходного файла неопределено при принудительном завершении\
\nКомманды: \
\n1 - Заполнить исходные матрицы используя данные из файла\
\n2 - Заполнить исходные матрицы вручную\
\n3 - Вывести исходные матрицы\
\n4 - Сложение матриц стандартным образом\
\n5 - Сложение матриц заданным образом\
\n6 - Получения таблицы производительности\
\n0 - Завершить работу программы\n"

int main()
{    
    int **m_1_classic = NULL;
    int **m_2_classic = NULL;
    matrix_t m_1 = {NULL, NULL, NULL};
    matrix_t m_2 = {NULL, NULL, NULL};
    size_t count_el = 0;
    int row = 0, col = 0;
    int command = -1;

    puts(TASK);
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
        // printf("count_el %zu", count_el);
        switch (command)
        {
            case 1:
                if (fscanf_matrixs(FILE_IN, &m_1_classic, &m_2_classic, &row, &col, &m_1, &m_2, &count_el, 1))
                    puts("Ошибка автоматического заполнения матриц, перепроверьте исходные данные");
                break;
            case 2:
                if (input_matrixs(&m_1_classic, &m_2_classic, &row, &col, &m_1, &m_2, &count_el))
                    puts("Ошибка заполнения матриц, попробуйте ещё раз");
                break;
            case 3:
                if (print_matrixs(m_1, m_2, count_el, col))
                    puts("Ошибка, печатать нечего, перепроверьте корректность данных");
                break;
            case 4:
                if (summary_matrix_classic(m_1_classic, m_2_classic, row, col, 1))
                    puts("Ошибка сложения матриц, перепроверьте данные");
                break;
            case 5:
                if (summary_matrix(m_1, m_2, count_el, col, 1))
                    puts("Ошибка сложения разреженных матриц, перепроверьте данные");
                break;
            case 6:
                efficency_table();
                break;
        }
    
    }

    free_matrix(m_1_classic, col);
    free_matrix(m_2_classic, col);

    free(m_1.A);
    free(m_1.IA);
    free(m_1.JA);
    
    free(m_2.A);
    free(m_2.IA);
    free(m_2.JA);  
    
    return 0;
}