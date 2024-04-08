#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <locale.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "struct.h"

// #define QU(x) #x
// #define QUH(x) QU(x)
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX_SIZE 1000
#define FILE_IN "file_in.txt"
// #define FILE_OUT "file_out.txt"
#define COUNT_TESTS 100
#define TEST "test.txt"

#define MENU "\
\nИсходные данные хранятся в файле file_in.txt. Программа не будет работать корректно, если исходный файл не существует.\
\nМаксимальное количество произведений обрабатываемых программой ограничено 1000\
\nСодержимое исходного файла неопределено при принудительном завершении\
\nКомманды: \
\n1 - Получения таблицы производительности\
\n2 - Вывод меню справки\
\n3 - Вывод таблицы произведений\
\n4 - Ввести новое произведение\
\n5 - Удалить произведение по индексу\
\n6 - Вывести таблицу отсортированную с помощью таблицы ключей (оптимизированная сортировка)\
\n7 - Вывести таблицу отсортированную с помощью таблицы ключей (неоптимизированная сортировка)\
\n8 - Вывести отсортированную таблицу (оптимизированная сортировка)\
\n9 - Вывести отсортированную таблицу (неоптимизированная сортировка)\
\n10 - Вывести отсортированную таблицу ключей\
\n11 - Вывести список всех романов указанного автора\
\n0 - Завершить работу программы"

typedef struct
{
    int index;
    char const *author;
} key_table_item_t;

unsigned long long cur_ms_gettimeofday()
{
	struct timeval timeval;
	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000000 + timeval.tv_usec);
}

void print_item_key_table(key_table_item_t *table)
{
    printf("%3d|%*s|", table->index, MAX_LEN_AUTHOR, table->author);
}

void print_arr_with_key_table(library_item_t *arr, key_table_item_t *key, size_t size)
{
    print_header();
    for (size_t i = 0; i < size; i++)
    {
        printf("|");
        printf("%3zu", i);
        print_literature(&(arr[key[i].index]));
        puts("");
    }
    print_line();
    puts("");
}

void print_literatures(library_item_t *arr, size_t size)
{
    print_header();
    for (size_t i = 0; i < size; i++)
    {
        printf("|");
        printf("%3zu", i);
        print_literature(&(arr[i]));
        puts("");
    }
    print_line();
    puts("");
}

void swap_key_table(key_table_item_t *a, key_table_item_t *b)
{
    key_table_item_t tmp;
    tmp.index = a->index;
    tmp.author = a->author;

    a->index = b->index;
    a->author = b->author;

    b->index = tmp.index;
    b->author = tmp.author;
}

void init_key_table(key_table_item_t *dst, library_item_t *src, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        dst[i].index = i;
        dst[i].author = src[i].author;
    }
}

void sort_lib(library_item_t *arr, size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = 0; j < size - 1 - i; j++)
            if (strcmp(arr[j].author, arr[j + 1].author) > 0)
                swap_literature(&arr[j], &arr[j + 1]);
}
void fast_sort_lib(library_item_t *arr, size_t size)
{
    for (size_t i = 1; i < size; i++) {
        library_item_t tmp = arr[i];
        size_t j = i;
        while (j > 0 && strcmp(arr[j - 1].author, tmp.author) > 0) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = tmp;
    }
}

void sort_key_table(key_table_item_t *arr, size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = 0; j < size - 1 - i; j++)
            if (strcmp(arr[j].author, arr[j + 1].author) > 0)
                swap_key_table(&arr[j], &arr[j + 1]);
}
void fast_sort_key_table(key_table_item_t *arr, size_t size)
{
    for (size_t i = 1; i < size; i++) {
        key_table_item_t tmp = arr[i];
        size_t j = i;
        while (j > 0 && strcmp(arr[j - 1].author, tmp.author) > 0) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = tmp;
    }
}

void print_filter_arr(library_item_t *arr, size_t size, char *search_author)
{
    int tmp = 0;
    int count = 0;
    for (size_t i = 0; i < size; i++)
        if (strcmp(search_author, arr[i].author) == 0 && 
            arr[i].type == il && 
            arr[i].item.il == novel)
            tmp++;
    if (tmp)
    {
        print_header();
        for (size_t i = 0; i < size; i++)
            if (strcmp(search_author, arr[i].author) == 0 && 
                arr[i].type == il && 
                arr[i].item.il == novel)
            {
                printf("|%3d", count);
                print_literature(&arr[i]);
                puts("");
                count++;
            }
        print_line();
        puts("");
    }
    else
        puts("Ничего не найдено");
}

int get_avg_sort_time(library_item_t *arr, size_t size, void (*sort)(library_item_t *arr, size_t size))
{
    int time = 0;
    library_item_t *tmp_arr = calloc(size, sizeof(library_item_t));
    if (tmp_arr == NULL)
    {
        puts("Недостаточно памяти для проведения подсчётов");
        return -1;
    }
    for (int i = 0; i < COUNT_TESTS; ++i)
    {
        // memcpy(*pb_dst, pb_src, (*pe_dst - *pb_dst) * sizeof(int));
        memcpy(tmp_arr, arr, MAX_SIZE * sizeof(library_item_t));
        unsigned long long start_time = cur_ms_gettimeofday();
        sort(tmp_arr, size);
        unsigned long long finish_time = cur_ms_gettimeofday();
        time += (finish_time - start_time);
    }
    free(tmp_arr);

    return time / COUNT_TESTS;
}

int get_avg_sort_time_keytable(library_item_t *arr, size_t size, void (*sort_key)(key_table_item_t *arr, size_t size))
{
    int time = 0;
    key_table_item_t key_table[size];
    for (int i = 0; i < COUNT_TESTS; ++i)
    {
        init_key_table(key_table, arr, size);
        unsigned long long start_time = cur_ms_gettimeofday();
        sort_key(key_table, size);
        unsigned long long finish_time = cur_ms_gettimeofday();
        time += (finish_time - start_time);
    }

    return time / COUNT_TESTS;
}

int main(void)
{
    setlocale(LC_ALL, "ru");
    library_item_t *lib = calloc(MAX_SIZE, sizeof(library_item_t));
    if (lib == NULL)
    {
        puts("Ошибка недостататочно памяти");
        exit(404);
    }    
    FILE *file = fopen(FILE_IN, "r");
    if (file == NULL)
    {
        puts("Ошибка открытия файла");
        return 5;
    }
    
    size_t size = 0;
    while (size < MAX_SIZE && !fscan_literature(&(lib[size++]), file));
    if (size == 0) {
        puts("Некорректный исходный файл "FILE_IN", исправьте и попробуйте снова");
        fclose(file);
        return 1;
    }
    fclose(file);
    system("clear");

    puts(MENU);
    int rc;
    int sort, f_sort, key, f_key;
    size_t ind;
    unsigned long long start_time, finish_time;
    key_table_item_t key_table[size];
    size_t mem_add;
    library_item_t *copy_lib;
    char search_author[MAX_LEN_AUTHOR + 2];

    int command = -1;
    while (command != 0)
    {
        printf("Всего произведений: %zu\n", size);
        puts("Введите команду:");
        while ((fscanf(stdin, "%d", &command) != 1 || command < 0 || command > 11)) 
        {
            puts("Некорректная комманда");
            puts("Введите команду:");
            clean_stdin();
        }
        clean_stdin();

        switch (command)
        {
            // Таблица производительности
            case 1:
                // system("clear");
                sort = get_avg_sort_time(lib, size, sort_lib);
                f_sort = get_avg_sort_time(lib, size, fast_sort_lib);
                key = get_avg_sort_time_keytable(lib, size, sort_key_table);
                f_key = get_avg_sort_time_keytable(lib, size, fast_sort_key_table);
                if (sort < 0 || f_sort < 0 || key < 0 || f_key < 0)
                    continue;
                puts("Время указано в мкс, затраты памяти в байтах");
                for (size_t i = 0; i < 15 + 25 + 25 + 25 + 25 + 6; i++)
                    printf("-");
                printf("\n|%15s|%25s|%25s|%25s|%25s|\n", "", "Sort", "Fast sort", "Sort(key table)", "Fast sort(key table)");
                for (size_t i = 0; i < 15 + 25 + 25 + 25 + 25 + 6; i++)
                    printf("-");

                printf("\n|%15s|%25d|%25d|%25d|%25d|", "Average time", sort, f_sort, key, f_key);
                printf("\n|%15s|%25zu|%25zu|%25zu|%25zu|\n", "Memory", \
                    sizeof(library_item_t) * size, \
                    sizeof(library_item_t) * size, \
                    sizeof(library_item_t) * size + sizeof(key_table_item_t) * size, \
                    sizeof(library_item_t) * size + sizeof(key_table_item_t) * size);
                for (size_t i = 0; i < 15 + 25 + 25 + 25 + 25 + 6; i++)
                    printf("-");
                if (((sort > key ? sort : key) / 100) == 0 || ((f_sort > f_key ? f_sort : f_key) / 100) == 0)
                {
                    puts("");
                    break;
                }
                printf("\nTime efficiency key table(buble): %3d%%", key / ((sort > key ? sort : key) / 100));
                printf("\nTime efficiency key table(insert): %3d%%", f_key / ((f_sort > f_key ? f_sort : f_key) / 100));
                printf("\nTime efficiency  database: 100%%\n");
                break;
            // Меню
            case 2:
                puts(MENU);
                break;
            // Вся таблица
            case 3:
                print_header();
                for (size_t i = 0; i < size; i++)
                {
                    printf("|");
                    printf("%3zu", i);
                    print_literature(&(lib[i]));
                    puts("");
                }
                print_line();
                puts("");
                break;
            // Добавить произведение
            case 4:
                if (size >= MAX_SIZE)
                {
                    printf("Программа не поддерживает обработку более %d элементов\n", MAX_SIZE);
                    continue;
                }

                puts("Новый элемент будет добавлен в конец");
                if ((rc = fscan_literature(&(lib[size++]), stdin)))
                {
                    size--;
                    puts("Некорректный ввод, попробуйте ещё раз");
                }
                break;
                if (!size)
                {
                    puts("Пустая таблица не может быть обработана");
                    continue;
                }
                break;
            // Удалить произведение по индексу
            case 5:
                puts("Введите индекс удаляемого элемента, индексация с 0:");
                if (scanf("%zu", &ind) != 1)
                {
                    clean_stdin();
                    puts("Некорректный ввода индекса, попробуйте ещё раз");
                    continue;
                }
                clean_stdin();
                if (remove_literature(lib, &size, ind))
                {
                    puts("Не удалось удалить элемент по заданному индексу");
                    continue;
                }
                break;
            // Таблица
            case 6:
                if (!size)
                {
                    puts("Таблица пуста, сортировать нечего");
                    continue;
                }
                init_key_table(key_table, lib, size);
                start_time = cur_ms_gettimeofday();
                fast_sort_key_table(key_table, size);
                finish_time = cur_ms_gettimeofday();
                mem_add = sizeof(key_table_item_t) * size;
                print_arr_with_key_table(lib, key_table, size);
                printf("Отсортировано за %llu мкс\nДополнительно использовано %zu байт памяти\n",\
                        finish_time - start_time, mem_add);
                break;
            // Таблица
            case 7:
                if (!size)
                {
                    puts("Таблица пуста, сортировать нечего");
                    continue;
                }
                init_key_table(key_table, lib, size);
                start_time = cur_ms_gettimeofday();
                sort_key_table(key_table, size);
                finish_time = cur_ms_gettimeofday();
                mem_add = sizeof(key_table_item_t) * size;
                print_arr_with_key_table(lib, key_table, size);
                printf("Отсортировано за %llu мкс\nДополнительно использовано %zu байт памяти\n",\
                        finish_time - start_time, mem_add);
                break;
            // Таблица
            case 8:
                copy_lib = calloc(MAX_SIZE, sizeof(library_item_t));
                if (copy_lib == NULL)
                {
                    puts("Ошибка недостататочно памяти");
                    continue;
                }
                // memcpy(*pb_dst, pb_src, (*pe_dst - *pb_dst) * sizeof(int));
                memcpy(copy_lib, lib, MAX_SIZE * sizeof(library_item_t));
                if (!size)
                {
                    puts("Таблица пуста, сортировать нечего");
                    continue;
                }
                
                start_time = cur_ms_gettimeofday();
                fast_sort_lib(copy_lib, size);
                finish_time = cur_ms_gettimeofday();
                mem_add = 1;
                print_literatures(copy_lib, size);
                printf("Отсортировано за %llu мкс\nДополнительно использовано %zu байт памяти\n",\
                        finish_time - start_time, mem_add);
                free(copy_lib);
                break;
            // Таблица
            case 9:
                copy_lib = calloc(MAX_SIZE, sizeof(library_item_t));
                if (copy_lib == NULL)
                {
                    puts("Ошибка недостататочно памяти");
                    continue;
                }
                // memcpy(*pb_dst, pb_src, (*pe_dst - *pb_dst) * sizeof(int));
                memcpy(copy_lib, lib, MAX_SIZE * sizeof(library_item_t));
                if (!size)
                {
                    puts("Таблица пуста, сортировать нечего");
                    continue;
                }
                
                start_time = cur_ms_gettimeofday();
                sort_lib(copy_lib, size);
                finish_time = cur_ms_gettimeofday();
                mem_add = 1;
                print_literatures(copy_lib, size);
                printf("Отсортировано за %llu мкс\nДополнительно использовано %zu байт памяти\n",\
                        finish_time - start_time, mem_add);
                free(copy_lib);
                break;
            // Таблица ключей
            case 10:
                if (!size)
                {
                    puts("Таблица пуста, сортировать нечего");
                    continue;
                }
                init_key_table(key_table, lib, size);
                fast_sort_key_table(key_table, size);

                for (size_t i = 0; i < 3 + 6 + MAX_LEN_AUTHOR + 1; ++i)
                    printf("-");
                printf("\n|%3s|%3s|%*s|\n", "N", "Ind", MAX_LEN_AUTHOR, "Author");
                for (size_t i = 0; i < 3 + 6 + MAX_LEN_AUTHOR + 1; ++i)
                    printf("-");
                puts("");
                for (size_t i = 0; i < size; i++)
                {
                    printf("|%3zu|", i);
                    print_item_key_table(&key_table[i]);
                    puts("");
                }
                for (size_t i = 0; i < 3 + 6 + MAX_LEN_AUTHOR + 1; ++i)
                    printf("-");
                puts("");
                break;
            // Романы по указанному автору
            case 11:                      
                if (!size)
                {
                    puts("Таблица пуста, сортировать нечего");
                    continue;
                }
                printf("Введите фамилию автора (максимальная длина %d): \n", MAX_LEN_AUTHOR);
                while (fscan_string(search_author, MAX_LEN_AUTHOR, stdin)) 
                {
                    puts("Автор указан некорректно");
                    continue;
                }

                print_filter_arr(lib, size, search_author);
                break;
        }
    }

    free(lib);
    // fclose(file);
    return 0;
}
