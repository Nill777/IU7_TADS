#include <string.h>
#include "func.h"
#include "struct.h"
#include "constants.h"

int counter = 0;

void clean_stdin(void)
{
    char c;
    do
        c = getchar();
    while (c != '\n');
}

int fscan_string(char *dst, size_t max_len, FILE* file)
{
    char *res = fgets(dst, max_len + 2, file);
    if (res == NULL)
        return 1;
    dst[strcspn(dst, "\n")] = '\0';
    size_t len = strlen(dst);

    if (len > max_len)
    {
        if (file == stdin)
            clean_stdin();
        return 2;
    }
    if (!len)
        return 3;

    return 0;
}

int fscan_technical(technical_t *dst, FILE *file)
{
    if (file == stdin)
        printf("Введите название индустрии (максимальная длина %d): \n", MAX_LEN_INDUSTRY);
    while (fscan_string(dst->industry, MAX_LEN_INDUSTRY, file) && (file == stdin || !feof(file))) 
    {
        puts("Название индустрии указано некорректно");
        if (file == stdin)
            printf("Введите название индустрии (максимальная длина %d): \n", MAX_LEN_INDUSTRY);
    }
    if (feof(file))
        return 1;

    size_t national;
    if (file == stdin)
        puts("Введите тип литературы:\
            \n0 - зарубежная\
            \n1 - отечественная");
    int tmp = 0;
    while ((fscanf(file, "%zu", &national) != 1 || national > 1) && (file == stdin || !feof(file))) 
    {
        tmp++;
        if (tmp == 3)
            return 3;
        printf("%zu %s", national, dst->industry);
        puts("Тип литературы указан некорректно");
        if (file == stdin)
            puts("Введите тип литературы:\
                \n0 - зарубежная\
                \n1 - отечественная");
        // ?
        if (file == stdin)
            clean_stdin();
    }       
    if (file == stdin)
        clean_stdin();
    if (feof(file))
        return 2;
    dst->national = national;

    size_t translated;
    if (file == stdin)
        puts("Введите тип литературы:\
            \n0 - не переводная\
            \n1 - переводная");
    while ((fscanf(file, "%zu", &translated) != 1 || translated > 1) && (file == stdin || !feof(file))) 
    {
        puts("Тип литературы указан некорректно");
        if (file == stdin)
            puts("Введите тип литературы:\
                \n0 - не переводная\
                \n1 - переводная");
        // ?
        if (file == stdin)
            clean_stdin();
    }       
    if (file == stdin)
        clean_stdin();
    if (feof(file))
        return 3;
    dst->translated = translated;

    int year;
    if (file == stdin)
        puts("Введите год издания:");
    while ((fscanf(file, "%d", &year) != 1 || year < 0 || year > 2023) && (file == stdin || !feof(file))) 
    {
        puts("Год издания указан некорректно");
        if (file == stdin)
            puts("Введите год издания:");
        if (file == stdin)
            clean_stdin();
    }       
    if (file == stdin)
        clean_stdin();
    if (feof(file))
        return 4;
    dst->year = year;

    return 0;
}

int fscan_imaginative(imaginative_t *dst, FILE *file)
{
    int type;
    if (file == stdin)
        puts("Введите вид литературы:\
            \n1 - роман\
            \n2 - пьеса\
            \n3 - поэзия");
    while ((fscanf(file, "%d", &type) != 1 || type < 1 || type > 3) && (file == stdin || !feof(file))) 
    {
        puts("Вид литературы указан некорректно");
        if (file == stdin)
            puts("Введите вид литературы:\
                \n1 - роман\
                \n2 - пьеса\
                \n3 - поэзия");
        // ?
        if (file == stdin)
            clean_stdin();
    }       
    if (file == stdin)
        clean_stdin();
    if (feof(file))
        return 1;
    *dst = type;

    return 0;
}

int fscan_children(children_t *dst, FILE *file)
{
    int age;
    if (file == stdin)
        puts("Введите возрастное ограничение:");
    while ((fscanf(file, "%d", &age) != 1 || age < 0 || age > 18) && (file == stdin || !feof(file))) 
    {
        puts("Возрастное ограничение указано некорректно");
        if (file == stdin)
            puts("Введите возрастное ограничение:");
        if (file == stdin)
            clean_stdin();
    }       
    if (file == stdin)
        clean_stdin();
    if (feof(file))
        return 1;
    dst->age = age;

    int type;
    if (file == stdin)
        puts("Введите вид литературы:\
            \n1 - сказки\
            \n2 - стихи");
    while ((fscanf(file, "%d", &type) != 1 || type < 1 || type > 2) && (file == stdin || !feof(file))) 
    {
        puts("Вид литературы указан некорректно");
        if (file == stdin)
            puts("Введите вид литературы:\
                \n1 - сказки\
                \n2 - стихи");
        // ?
        if (file == stdin)
            clean_stdin();
    }       
    if (file == stdin)
        clean_stdin();
    if (feof(file))
        return 2;
    dst->type = type;

    return 0;
}

int fscan_literature(library_item_t *dst, FILE *file)
{
    if (file == stdin)
        printf("Введите фамилию автора (максимальная длина %d): \n", MAX_LEN_AUTHOR);
    while (fscan_string(dst->author, MAX_LEN_AUTHOR, file) && (file == stdin || !feof(file))) 
    {
        puts("Автор указан некорректно");
        if (file == stdin)
            printf("Введите фамилию автора (максимальная длина %d): \n", MAX_LEN_AUTHOR);
    }
    if (feof(file))
        return 1;
    if (file == stdin)
        printf("Введите название произведения (максимальная длина %d): \n", MAX_LEN_TITLE);
    while (fscan_string(dst->title, MAX_LEN_TITLE, file) && (file == stdin || !feof(file))) 
    {
        puts("Название произведения указано некорректно");
        if (file == stdin)
            printf("Введите название произведения (максимальная длина %d): \n", MAX_LEN_TITLE);
    }
    if (feof(file))
        return 2;
    if (file == stdin)
        printf("Введите название издательства (максимальная длина %d): \n", MAX_LEN_PUBLISH);
    while (fscan_string(dst->publish, MAX_LEN_PUBLISH, file) && (file == stdin || !feof(file))) 
    {
        puts("Название издательства указано некорректно");
        if (file == stdin)
            printf("Введите название издательства (максимальная длина %d): \n", MAX_LEN_PUBLISH);
    }
    if (feof(file))
        return 3;
    int pages;
    if (file == stdin)
        puts("Введите количество страниц в произведении (0-10000):");
    while ((fscanf(file, "%d", &pages) != 1 || pages <= 0 || pages > 10000) && (file == stdin || !feof(file))) 
    {
        puts("Количество страниц указано некорректно");
        if (file == stdin)
            puts("Введите количество страниц в произведении (0-10000):");
        if (file == stdin)
            clean_stdin();
    }       
    if (file == stdin)
        clean_stdin();
    if (feof(file))
        return 4;
    dst->pages = pages;

    int type;
    if (file == stdin)
        puts("Введите вид литературы:\
            \n1 - техническая\
            \n2 - художественная\
            \n3 - детская");
    while ((fscanf(file, "%d", &type) != 1 || type < tl || type > cl) && (file == stdin || !feof(file))) 
    {
        puts("Вид литературы указан некорректно");
        if (file == stdin)
            puts("Введите вид литературы:\
                \n1 - техническая\
                \n2 - художественная\
                \n3 - детская");
        // ?
        if (file == stdin)
            clean_stdin();
    }       
    if (file == stdin)
        clean_stdin();
    if (feof(file))
        return 5;
    dst->type = type;
    // printf("type %d ", type);
    int rc;
    switch (type)
    {
        case tl:
            if ((rc = fscan_technical(&(dst->item.tl), file)))
                return rc;
            break;
        case il:
            if ((rc = fscan_imaginative(&(dst->item.il), file)))
                return rc;
            break;
        case cl:
            if ((rc = fscan_children(&(dst->item.cl), file)))
                return rc;
            break;
    }

    return 0;
}

void swap_literature(library_item_t *a, library_item_t *b)
{
    char tmp;
    char *pl = (char *)a;
    char *pr = (char *)b;

    for (size_t i = 0; i < sizeof(library_item_t); i++, pl++, pr++)
    {
        tmp = *pl;
        *pl = *pr;
        *pr = tmp;
    }
}

void print_line(void)
{
    size_t len = 3 + 
                MAX_LEN_AUTHOR + 
                MAX_LEN_TITLE + 
                MAX_LEN_PUBLISH + 
                5 + 
                15 + 
                3 + 
                7 + 
                MAX_LEN_INDUSTRY + 
                10 + 
                15 + 
                5 + 
                13;
    for (size_t i = 0; i < len; i++)
        printf("-");
}

void print_header(void)
{
    puts("");
    print_line();
    puts("");
    printf("|");
    printf("%3s", "N");
    printf("|");
    printf("%*s", MAX_LEN_AUTHOR, "Autor");
    printf("|");
    printf("%*s", MAX_LEN_TITLE, "Title");
    printf("|");
    printf("%*s", MAX_LEN_PUBLISH, "Publish");
    printf("|");
    printf("%5s", "Pages");
    printf("|");
    printf("%15s", "Type");
    printf("|");
    printf("%3s", "Age");
    printf("|");
    printf("%7s", "Type");
    printf("|");
    printf("%*s", MAX_LEN_INDUSTRY, "Industry");
    printf("|");
    printf("%10s", "National");
    printf("|");
    printf("%15s", "Translated");
    printf("|");
    printf("%5s", "Year");
    printf("|");
    puts("");
    print_line();
    puts("");
}

void print_literature(library_item_t *src)
{
    printf("|");
    printf("%*s", MAX_LEN_AUTHOR, src->author);
    printf("|");
    printf("%*s", MAX_LEN_TITLE, src->title);
    printf("|");
    printf("%*s", MAX_LEN_PUBLISH, src->publish);
    printf("|");
    printf("%5d", src->pages);
    printf("|");
    switch (src->type)
    {
        case tl:
            printf("%15s", "technical");
            printf("|");
            printf("%3s", "");
            printf("|");
            printf("%7s", "");
            printf("|");
            printf("%*s", MAX_LEN_INDUSTRY, src->item.tl.industry);
            printf("|");
            if (src->item.tl.national)
                printf("%10s", "national");
            else
                printf("%10s", "foreign");
            printf("|");
            if (src->item.tl.translated)
                printf("%15s", "translated");
            else
                printf("%15s", "untranslated");
            printf("|");
            printf("%5d", src->item.tl.year);
            printf("|");
            break;
        case il:
            printf("%15s", "imaginative");
            printf("|");
            printf("%3s", "");
            printf("|");
            switch (src->item.il)
            {
                case 1:
                    printf("%7s", "novel");
                    break;
                case 2:
                    printf("%7s", "play");
                    break;
                case 3:
                    printf("%7s", "poetry");
                    break;
            }
            printf("|");
            printf("%*s", MAX_LEN_INDUSTRY, "");
            printf("|");
            printf("%10s", "");
            printf("|");
            printf("%15s", "");
            printf("|");
            printf("%5s", "");
            printf("|");
            break;
        case cl:
            printf("%15s", "children");
            printf("|");
            printf("%3d", src->item.cl.age);
            printf("|");
            switch (src->item.cl.type)
            {
                case 1:
                    printf("%7s", "tales");
                    break;
                case 2:
                    printf("%7s", "poetry");
                    break;
            }
            printf("|");
            printf("%*s", MAX_LEN_INDUSTRY, "");
            printf("|");
            printf("%10s", "");
            printf("|");
            printf("%15s", "");
            printf("|");
            printf("%5s", "");
            printf("|");
            break;
    }
}

void copy_literature(library_item_t *dst, library_item_t const *src)
{
    memcpy(dst, src, sizeof(library_item_t));
}

int remove_literature(library_item_t *arr, size_t *size, size_t ind)
{
    if (ind >= *size)
        return 1;
    for (size_t i = ind; i < *size - 1; i++)
        swap_literature(&(arr[i]), &(arr[i + 1]));
    (*size)--;
    return 0;
}


