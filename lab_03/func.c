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

void free_matrix(int **matrix, size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

int fscanf_matrixs(char *src, int ***m_1_classic, int ***m_2_classic, int *row, int *col, matrix_t *m_1, matrix_t *m_2, size_t *count_el, size_t print_flag)
{
    int count = 0;

    FILE *file = fopen(src, "r");
    if (file == NULL)
    {
        puts("Ошибка открытия файла");
        return 1;
    }

    if (fscanf(file, "%d\n", row) != 1 || *row <= 0)
        return 2;
    if (fscanf(file, "%d\n", col) != 1 || *col <= 0)
        return 3;
    if (fscanf(file, "%d\n", &count) != 1 || count <= 0 || count > *row * *col)
        return 4;
    *count_el = count;
    // Выделение памяти
    *m_1_classic = calloc(*col, sizeof(int *));
    if (*m_1_classic == NULL)
    {
        puts("Ошибка, невозможно выделить память");
        exit(404);
    }
    for (int i = 0; i < *col; i++)
    {
        (*m_1_classic)[i] = calloc(*row, sizeof(int));
        if ((*m_1_classic)[i] == NULL)
        {
            free_matrix(*m_1_classic, *col);
            puts("Ошибка, невозможно выделить память");
            exit(404);
        }
    }

    *m_2_classic = calloc(*col, sizeof(int *));
    if (*m_2_classic == NULL)
    {
        free_matrix(*m_1_classic, *col);
        puts("Ошибка, невозможно выделить память");
        exit(405);
    }
    for (int i = 0; i < *col; i++)
    {
        (*m_2_classic)[i] = calloc(*row, sizeof(int));
        if ((*m_2_classic)[i] == NULL)
        {
            free_matrix(*m_1_classic, *col);
            free_matrix(*m_2_classic, *col);
            puts("Ошибка, невозможно выделить память");
            exit(405);
        }
    }

    // m_1 = calloc(1, sizeof(matrix_t));
    // if (m_1 == NULL)
    // {
    //     free_matrix(*m_1_classic, *col);
    //     free_matrix(*m_2_classic, *col);
    //     puts("Ошибка, невозможно выделить память");
    //     exit(406);
    // }
    m_1->A = calloc(count, sizeof(int));
    if (m_1->A == NULL)
    {
        free_matrix(*m_1_classic, *col);
        free_matrix(*m_2_classic, *col);
        // free(m_1);
        puts("Ошибка, невозможно выделить память");
        exit(406);
    }
    m_1->IA = calloc(count, sizeof(int));
    if (m_1->IA == NULL)
    {
        free_matrix(*m_1_classic, *col);
        free_matrix(*m_2_classic, *col);
        free(m_1->A);
        // free(m_1);
        puts("Ошибка, невозможно выделить память");
        exit(406);
    }
    m_1->JA = calloc(*col, sizeof(int));
    if (m_1->JA == NULL)
    {
        free_matrix(*m_1_classic, *col);
        free_matrix(*m_2_classic, *col);
        free(m_1->A);
        free(m_1->IA);
        // free(m_1);
        puts("Ошибка, невозможно выделить память");
        exit(406);
    }

    // m_2 = calloc(1, sizeof(matrix_t));
    // if (m_2 == NULL)
    // {
    //     free(m_1_classic);
    //     free(m_2_classic);
    //     free(m_1);
    //     puts("Ошибка, невозможно выделить память");
    //     exit(407);
    // }
    m_2->A = calloc(count, sizeof(int));
    if (m_2->A == NULL)
    {
        free_matrix(*m_1_classic, *col);
        free_matrix(*m_2_classic, *col);
        free(m_1->A);
        free(m_1->IA);
        free(m_1->JA);
        // free(m_1);
        // free(m_2);
        puts("Ошибка, невозможно выделить память");
        exit(407);
    }
    m_2->IA = calloc(count, sizeof(int));
    if (m_2->IA == NULL)
    {
        free_matrix(*m_1_classic, *col);
        free_matrix(*m_2_classic, *col);
        free(m_1->A);
        free(m_1->IA);
        free(m_1->JA);
        free(m_2->A);
        // free(m_1);
        // free(m_2);
        puts("Ошибка, невозможно выделить память");
        exit(407);
    }
    m_2->JA = calloc(*col, sizeof(int));
    if (m_2->JA == NULL)
    {
        free_matrix(*m_1_classic, *col);
        free_matrix(*m_2_classic, *col);
        
        free(m_1->A);
        free(m_1->IA);
        free(m_1->JA);
        // free(m_1);
        
        free(m_2->A);
        free(m_2->IA);
        // free(m_2);
        puts("Ошибка, невозможно выделить память");
        exit(407);
    }
    
    for (int i = 0; i < *col; i++)
        m_1->JA[i] = m_2->JA[i] = -1;
    // puts("@#$%^&");
    // Ввод элементов
    int tmp_col, tmp_row, tmp_el;
    for (int i = 0; i < count; i++)
    {
        if (fscanf(file, "%d\n", &tmp_row) != 1 || tmp_row < 0 || tmp_row >= *row)
            return 5;
        if (fscanf(file, "%d\n", &tmp_col) != 1 || tmp_col < 0 || tmp_col >= *col)
            return 6;
        if (fscanf(file, "%d\n", &tmp_el) != 1 || tmp_el == 0)
            return 7;
        (*m_1_classic)[tmp_row][tmp_col] = tmp_el;
    }
    int tmp_count = 0;
    for (int j = 0; j < *col; j++)
        for (int i = 0; i < *row; i++)
            if ((*m_1_classic)[i][j] != 0)
            {
                (m_1->A)[tmp_count] = (*m_1_classic)[i][j];
                (m_1->IA)[tmp_count] = i;
                if ((m_1->JA)[j] == -1)
                    (m_1->JA)[j] = tmp_count;
                tmp_count++;
            }
    // puts("@#$%^&");
    for (int i = 0; i < count; i++)
    {
        if (fscanf(file, "%d\n", &tmp_row) != 1 || tmp_row < 0 || tmp_row >= *row)
            return 8;
        if (fscanf(file, "%d\n", &tmp_col) != 1 || tmp_col < 0 || tmp_col >= *col)
            return 9;
        if (fscanf(file, "%d\n", &tmp_el) != 1 || tmp_el == 0)
            return 10;
        // printf("%d %d %d", i, tmp_row, tmp_col);
        (*m_2_classic)[tmp_row][tmp_col] = tmp_el;
    }
    tmp_count = 0;
    for (int j = 0; j < *col; j++)
        for (int i = 0; i < *row; i++)
            if ((*m_2_classic)[i][j] != 0)
            {
                (m_2->A)[tmp_count] = (*m_2_classic)[i][j];
                (m_2->IA)[tmp_count] = i;
                if ((m_2->JA)[j] == -1)
                    (m_2->JA)[j] = tmp_count;
                tmp_count++;
            }
            
    //     (m_2->A)[i] = tmp_el;
    //     (m_2->IA)[i] = tmp_row;
    //     if ((m_2->JA)[i] == -1)
    //         (m_2->JA)[tmp_col] = i;
    //     // print_matrix(*m_2, i + 1, *col);
    // }
    fclose(file);
    if (print_flag)
        puts("Матрицы заполнены автоматически");
    return 0;
}

int input_matrixs(int ***m_1_classic, int ***m_2_classic, int *row, int *col, matrix_t *m_1, matrix_t *m_2, size_t *count_el)
{
    int count = 0;

    puts("Введите количество строк матрицы:");
    while (scanf("%d", row) != 1 || *row <= 0)
    {
        puts("Некорректное количество строк");
        clean_stdin();
    }
    clean_stdin();
    puts("Введите количество столбцов матрицы:");
    while (scanf("%d", col) != 1 || *col <= 0)
    {
        puts("Некорректное количество столбцов");
        clean_stdin();
    }
    clean_stdin();
    puts("Введите количество ненулевых элементов матрицы:");
    while (scanf("%d", &count) != 1 || count <= 0 || count > *row * *col)
    {
        puts("Некорректное количество ненулевых элементов");
        clean_stdin();
    }
    clean_stdin();
    *count_el = count;
    // Выделение памяти
    *m_1_classic = calloc(*col, sizeof(int *));
    if (m_1_classic == NULL)
    {
        puts("Ошибка, невозможно выделить память");
        exit(404);
    }
    for (int i = 0; i < *col; i++)
    {
        (*m_1_classic)[i] = calloc(*row, sizeof(int));
        if ((*m_1_classic)[i] == NULL)
        {
            free_matrix(*m_1_classic, *col);
            puts("Ошибка, невозможно выделить память");
            exit(404);
        }
    }

    *m_2_classic = calloc(*col, sizeof(int *));
    if (m_2_classic == NULL)
    {
        free_matrix(*m_1_classic, *col);
        puts("Ошибка, невозможно выделить память");
        exit(405);
    }
    for (int i = 0; i < *col; i++)
    {
        (*m_2_classic)[i] = calloc(*row, sizeof(int));
        if ((*m_2_classic)[i] == NULL)
        {
            free_matrix(*m_1_classic, *col);
            free_matrix(*m_2_classic, *col);
            puts("Ошибка, невозможно выделить память");
            exit(405);
        }
    }

    // m_1 = calloc(1, sizeof(matrix_t));
    // if (m_1 == NULL)
    // {
    //     free_matrix(*m_1_classic, *col);
    //     free_matrix(*m_2_classic, *col);
    //     puts("Ошибка, невозможно выделить память");
    //     exit(406);
    // }
    m_1->A = calloc(count, sizeof(int));
    if (m_1->A == NULL)
    {
        free_matrix(*m_1_classic, *col);
        free_matrix(*m_2_classic, *col);
        // free(m_1);
        puts("Ошибка, невозможно выделить память");
        exit(406);
    }
    m_1->IA = calloc(count, sizeof(int));
    if (m_1->IA == NULL)
    {
        free_matrix(*m_1_classic, *col);
        free_matrix(*m_2_classic, *col);
        free(m_1->A);
        // free(m_1);
        puts("Ошибка, невозможно выделить память");
        exit(406);
    }
    m_1->JA = calloc(*col, sizeof(int));
    if (m_1->JA == NULL)
    {
        free_matrix(*m_1_classic, *col);
        free_matrix(*m_2_classic, *col);
        free(m_1->A);
        free(m_1->IA);
        // free(m_1);
        puts("Ошибка, невозможно выделить память");
        exit(406);
    }

    // m_2 = calloc(1, sizeof(matrix_t));
    // if (m_2 == NULL)
    // {
    //     free(m_1_classic);
    //     free(m_2_classic);
    //     free(m_1);
    //     puts("Ошибка, невозможно выделить память");
    //     exit(407);
    // }
    m_2->A = calloc(count, sizeof(int));
    if (m_2->A == NULL)
    {
        free_matrix(*m_1_classic, *col);
        free_matrix(*m_2_classic, *col);
        free(m_1->A);
        free(m_1->IA);
        free(m_1->JA);
        // free(m_1);
        // free(m_2);
        puts("Ошибка, невозможно выделить память");
        exit(407);
    }
    m_2->IA = calloc(count, sizeof(int));
    if (m_2->IA == NULL)
    {
        free_matrix(*m_1_classic, *col);
        free_matrix(*m_2_classic, *col);
       
        free(m_1->A);
        free(m_1->IA);
        free(m_1->JA);
        free(m_2->A);
        // free(m_1);
        // free(m_2);
        puts("Ошибка, невозможно выделить память");
        exit(407);
    }
    m_2->JA = calloc(*col, sizeof(int));
    if (m_2->JA == NULL)
    {
        free_matrix(*m_1_classic, *col);
        free_matrix(*m_2_classic, *col);
        free(m_1->A);
        free(m_1->IA);
        free(m_1->JA);
        free(m_2->A);
        free(m_2->IA);
        // free(m_1);
        // free(m_2);
        puts("Ошибка, невозможно выделить память");
        exit(407);
    }
    
    for (int i = 0; i < *col; i++)
        m_1->JA[i] = m_2->JA[i] = -1;

    // Ввод элементов
    int tmp_col, tmp_row, tmp_el;
    puts("Введите значения элементов 1 матрицы");
    for (int i = 0; i < count; i++)
    {
        printf("Введите номер строки для заполнения (0 - %d):\n", *row - 1);
        while (scanf("%d", &tmp_row) != 1 || tmp_row < 0 || tmp_row >= *row)
        {
            puts("Некорректный номер строки");
            clean_stdin();
        }
        clean_stdin();

        printf("Введите номер столбца для заполнения (0 - %d):\n", *col - 1);
        while (scanf("%d", &tmp_col) != 1 || tmp_col < 0 || tmp_col >= *col)
        {
            puts("Некорректный номер столбца");
            clean_stdin();
        }
        clean_stdin();

        printf("Введите значение:\n");
        while (scanf("%d", &tmp_el) != 1 || tmp_el == 0)
        {
            puts("Некорректное значение");
            clean_stdin();
        }
        clean_stdin();
        (*m_1_classic)[tmp_row][tmp_col] = tmp_el;
    }
    int tmp_count = 0;
    for (int j = 0; j < *col; j++)
        for (int i = 0; i < *row; i++)
            if ((*m_1_classic)[i][j] != 0)
            {
                (m_1->A)[tmp_count] = (*m_1_classic)[i][j];
                (m_1->IA)[tmp_count] = i;
                if ((m_1->JA)[j] == -1)
                    (m_1->JA)[j] = tmp_count;
                tmp_count++;
            }
    puts("Введите значения элементов 2 матрицы");
    for (int i = 0; i < count; i++)
    {
        printf("Введите номер строки для заполнения (0 - %d):\n", *row - 1);
        while (scanf("%d", &tmp_row) != 1 || tmp_row < 0 || tmp_row >= *row)
        {
            puts("Некорректный номер строки");
            clean_stdin();
        }
        clean_stdin();

        printf("Введите номер столбца для заполнения (0 - %d):\n", *col - 1);
        while (scanf("%d", &tmp_col) != 1 || tmp_col < 0 || tmp_col >= *col)
        {
            puts("Некорректный номер столбца");
            clean_stdin();
        }
        clean_stdin();

        printf("Введите значение:\n");
        while (scanf("%d", &tmp_el) != 1 || tmp_el == 0)
        {
            puts("Некорректное значение");
            clean_stdin();
        }
        clean_stdin();
        (*m_2_classic)[tmp_row][tmp_col] = tmp_el;
    }

    tmp_count = 0;
    for (int j = 0; j < *col; j++)
        for (int i = 0; i < *row; i++)
            if ((*m_2_classic)[i][j] != 0)
            {
                (m_2->A)[tmp_count] = (*m_2_classic)[i][j];
                (m_2->IA)[tmp_count] = i;
                if ((m_2->JA)[j] == -1)
                    (m_2->JA)[j] = tmp_count;
                tmp_count++;
            }

    puts("Матрицы заполнены");
    return 0;
}

void print_matrix(matrix_t m, size_t count_el, int col)
{
    printf("Вектор A\n");
    for (size_t i = 0; i < count_el; i++)
        printf("%5d ", m.A[i]);
    printf("\nВектор IA\n");
    for (size_t i = 0; i < count_el; i++)
        printf("%5d ", m.IA[i]);
    printf("\nВектор JA\n");
    for (int i = 0; i < col; i++)
        printf("%5d ", m.JA[i]);
    puts("");
}

int print_matrixs(matrix_t m_1, matrix_t m_2, size_t count_el, int col)
{
    if (col <= 0 || count_el == 0)
        return 1;
    printf("Первая матрица\n");    
    print_matrix(m_1, count_el, col);
    puts("");
    printf("Вторая матрица:\n");
    print_matrix(m_2, count_el, col);
    puts("");
    return 0;
}

int summary_matrix_classic(int **m_1_classic, int **m_2_classic, int row, int col, size_t print_flag)
{
    int el;
    size_t count_el = 0;
    int **m_sum_classic = NULL;
    matrix_t m_sum = {NULL, NULL, NULL};
    if (!m_1_classic || !m_2_classic)
        return 1;
    if (row <= 0 || col <= 0)
        return 2;
    
    m_sum_classic = calloc(col, sizeof(int *));
    if (m_sum_classic == NULL)
    {
        puts("Ошибка, невозможно выделить память");
        return 3;
    }
    for (int i = 0; i < col; i++)
    {
        (m_sum_classic)[i] = calloc(row, sizeof(int));
        if ((m_sum_classic)[i] == NULL)
        {
            free_matrix(m_sum_classic, col);
            puts("Ошибка, невозможно выделить память");
            return 4;
        }
    }

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if ((m_sum_classic[i][j] = m_1_classic[i][j] + m_2_classic[i][j]) != 0)
                count_el++;

    if (print_flag)
    {
        m_sum.A = calloc(count_el, sizeof(int));
        if (m_sum.A == NULL)
        {
            free_matrix(m_sum_classic, col);
            puts("Ошибка, невозможно выделить память");
            exit(5);
        }
        m_sum.IA = calloc(count_el, sizeof(int));
        if (m_sum.IA == NULL)
        {
            free_matrix(m_sum_classic, col);
            free(m_sum.A);
            puts("Ошибка, невозможно выделить память");
            exit(6);
        }
        m_sum.JA = calloc(col, sizeof(int));
        if (m_sum.JA == NULL)
        {
            free_matrix(m_sum_classic, col);
            free(m_sum.A);
            free(m_sum.IA);
            puts("Ошибка, невозможно выделить память");
            exit(7);
        }
        for (int i = 0; i < col; i++)
            m_sum.JA[i] = -1;

        int tmp_count = 0;
        for (int j = 0; j < col; j++)
            for (int i = 0; i < row; i++)
                if ((el = m_sum_classic[i][j]) != 0)
                {
                    (m_sum.A)[tmp_count] = el;
                    (m_sum.IA)[tmp_count] = i;
                    if ((m_sum.JA)[j] == -1)
                        (m_sum.JA)[j] = tmp_count;
                    tmp_count++;
                }


        puts("Результат суммирования");
        print_matrix(m_sum, count_el, col);
        free(m_sum.IA);
        free(m_sum.A);
        free(m_sum.JA);
    }

    free_matrix(m_sum_classic, col);

    return 0;
}

int summary_matrix(matrix_t m_1, matrix_t m_2, size_t count_el, int col, size_t print_flag)
{
    matrix_t m_sum = {NULL, NULL, NULL};
    if (count_el == 0 || col <= 0)
        return 2;

    m_sum.A = calloc(2 * count_el, sizeof(int));
    if (m_sum.A == NULL)
    {
        puts("Ошибка, невозможно выделить память");
        exit(5);
    }
    m_sum.IA = calloc(2 * count_el, sizeof(int));
    if (m_sum.IA == NULL)
    {
        free(m_sum.A);
        puts("Ошибка, невозможно выделить память");
        exit(6);
    }
    m_sum.JA = calloc(col, sizeof(int));
    if (m_sum.JA == NULL)
    {
        free(m_sum.A);
        free(m_sum.IA);
        puts("Ошибка, невозможно выделить память");
        exit(7);
    }
    for (int i = 0; i < col; i++)
        m_sum.JA[i] = -1;
// !!!!!!!!!!!!!!
    size_t count_el_tmp = 0;
    for (int j = 0; j < col; j++)
    {
        if (m_1.JA[j] != -1)
        {
            m_sum.JA[j] = count_el_tmp;
            // Поиск индекса запоследнего элемента столбца
            int k = -1;
            for (int i = j + 1; i < col; i++)
                if (m_1.JA[i] != -1)
                {
                    k = m_1.JA[i];
                    break;
                }
            if (k == -1)
                k = count_el;

            for (int r = m_1.JA[j]; r < k; r++)
            {
                m_sum.A[count_el_tmp] = m_1.A[r];
                m_sum.IA[count_el_tmp] = m_1.IA[r];
                count_el_tmp++;
            }
        }
        if (m_2.JA[j] != -1)
        {
            if (m_sum.JA[j] == -1)
                m_sum.JA[j] = count_el_tmp;
            // Поиск индекса запоследнего элемента столбца
            int k = -1;
            for (int i = j + 1; i < col; i++)
                if (m_2.JA[i] != -1)
                {
                    k = m_2.JA[i];
                    break;
                }
            if (k == -1)
                k = count_el;

            for (int r = m_2.JA[j]; r < k; r++)
            {
                int f = 1;
                for (size_t q = m_sum.JA[j]; q < count_el_tmp; q++)
                {
                    if (m_sum.IA[q] == m_2.IA[r])
                    {
                        m_sum.A[q] += m_2.A[r];
                        f = 0;
                    }
                }
                if (f)
                {
                    m_sum.A[count_el_tmp] = m_2.A[r];
                    m_sum.IA[count_el_tmp] = m_2.IA[r];
                    count_el_tmp++;
                }
            }
        }
    }
    if (print_flag)
    {
        puts("Результат суммирования");
        print_matrix(m_sum, count_el_tmp, col);
    }

    free(m_sum.A);
    free(m_sum.IA);
    free(m_sum.JA);
    return 0;
}

void efficency_table(void)
{
    char file[30];
    puts("Время указано в мкс, затраты памяти в байтах");
    puts("TIME");
    for (size_t i = 0; i < 5 + 5 + 15 + 15 + 5; i++)
        printf("-");
    printf("\n|%5s|%5s|%15s|%15s|\n", "N", "%", "Regular matrix", "Sparse matrix");
    for (size_t i = 0; i < 5 + 5 + 15 + 15 + 5; i++)
        printf("-");
    puts("");

    for (size_t i = 100; i <= 300; i += 100)
    {
        size_t j = 10;
        unsigned long long start_time1;
        unsigned long long finish_time1;
        unsigned long long start_time2;
        unsigned long long finish_time2;
        for (; j <= 100; j += 10)
        {
            unsigned long long avg_time1 = 0;
            unsigned long long avg_time2 = 0;
            for (size_t k = 0; k < COUNT_TESTS; k++)
            {
                matrix_t m_1 = {NULL, NULL, NULL};
                matrix_t m_2 = {NULL, NULL, NULL};
                int **m_1_classic = NULL;
                int **m_2_classic = NULL;
                int row = i, col = i;
                size_t count_el = 0;
                sprintf(file, "./data/m_%zu_%zu%%.txt", i, j);
                // printf("%s", file);
                fscanf_matrixs(file, &m_1_classic, &m_2_classic, &row, &col, &m_1, &m_2, &count_el, 0);
                // system("clear");
                start_time1 = cur_mks_gettimeofday();
                summary_matrix_classic(m_1_classic, m_2_classic, row, col, 0);
                finish_time1 = cur_mks_gettimeofday();
                // system("clear");
                start_time2 = cur_mks_gettimeofday();
                summary_matrix(m_1, m_2, count_el, col, 0);
                finish_time2 = cur_mks_gettimeofday();
                // system("clear");
                free_matrix(m_1_classic, col);
                free_matrix(m_2_classic, col);
                
                free(m_1.A);
                free(m_1.IA);
                free(m_1.JA);
                
                free(m_2.A);
                free(m_2.IA);
                free(m_2.JA);

                avg_time1 += finish_time1 - start_time1;
                avg_time2 += finish_time2 - start_time2;
            }
            printf("|%5zu|%5zu|%15llu|%15llu|\n", i, j, avg_time1 / COUNT_TESTS, avg_time2 / COUNT_TESTS);
        }
        for (size_t i = 0; i < 5 + 5 + 15 + 15 + 5; i++)
            printf("-");
        puts("");
    }
    // for (size_t i = 0; i < 5 + 5 + 15 + 15 + 5; i++)
    //     printf("-");
    // puts("");

    puts("MEMORY");
    for (size_t i = 0; i < 5 + 5 + 15 + 15 + 5; i++)
        printf("-");
    printf("\n|%5s|%5s|%15s|%15s|\n", "N", "%", "Regular matrix", "Sparse matrix");
    for (size_t i = 0; i < 5 + 5 + 15 + 15 + 5; i++)
        printf("-");
    puts("");
    for (size_t i = 100; i <= 300; i += 100)
    {
        size_t j = 10;
        int row = i, col = i;
        size_t count_el = 0;
        for (; j <= 100; j += 10)
        {
            matrix_t m_1 = {NULL, NULL, NULL};
            matrix_t m_2 = {NULL, NULL, NULL};
            int **m_1_classic = NULL;
            int **m_2_classic = NULL;  
            sprintf(file, "./data/m_%zu_%zu%%.txt", i, j);
            fscanf_matrixs(file, &m_1_classic, &m_2_classic, &row, &col, &m_1, &m_2, &count_el, 0);
            // system("clear");
            free_matrix(m_1_classic, col);
            free_matrix(m_2_classic, col);
            
            free(m_1.A);
            free(m_1.IA);
            free(m_1.JA);
            
            free(m_2.A);
            free(m_2.IA);
            free(m_2.JA);
            printf("|%5zu|%5zu|%15lu|%15lu|\n", i, j, row * col * sizeof(int), col * sizeof(int) + count_el * sizeof(int) * 2);
        }
        for (size_t i = 0; i < 5 + 5 + 15 + 15 + 5; i++)
            printf("-");
        puts("");
    }
    // for (size_t i = 0; i < 5 + 5 + 15 + 15 + 5; i++)
    //     printf("-");
    // puts("");
}
