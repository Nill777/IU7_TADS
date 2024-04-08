#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bignum.h"

#ifndef BASE
#define BASE 10
#endif

#if BASE < 2
#error Base must be bigger then 1
#endif
#if BASE < 10
#pragma message "Output not in decimal"
#endif
#if BASE > 10
#pragma message "Incorrect work"
#endif

#define MAX_ORDER 99999
#define MIN_ORDER -99999

void bignum_init(bignum_t *a)
{
    memset(a, 0, sizeof(*a));
}

// 0 000001234 0 00012
void bignum_print_field(unsigned char *a, size_t alen)
{
    size_t i = 0;
    while (i < alen && a[i] == 0)
        i++;
    for (; i < alen; i++)
        printf("%c", a[i]);
}

void bigint_print(bignum_t *a)
{
    if (a->is_negative)
        printf("-");
    bignum_print_field(a->mantissa_field, MANTISSA_LEN);
}

void bigfloat_print(bignum_t *a)
{
    if (a->is_negative)
        printf("-");
    printf("0.");
    bignum_print_field(a->mantissa_field, MANTISSA_LEN);
    printf(" E %ld", a->order);
}

/* ...00000004321 to ...00000001234 */
void revers_num(unsigned char *a, size_t alen)
{
    size_t i = 0;
    int tmp;
    while (i < alen && a[i] == 0)
        i++;
    for (size_t j = alen - 1; i <= j - 1; i++, j--) {
        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}

int sbigint_scanf(bignum_t *a)
{
    int sign = 1;
    int c;
    size_t tmp_len = 0;
    int count = 0;
    char tmp_mantiss[MANTISSA_LEN + 1];
    for(size_t i = 0; (c = getchar()) != EOF; i++) {
        if (c == '-' && sign) {
            a->is_negative = 1;
            sign = 0; 
            continue;
        }
        else if (c == '0')
            continue;
        else if (isdigit(c) || c == '\n')
            break;
        else
            return 1;
    }

    do {
        if (count > MANTISSA_LEN)
            return 2;
        if (isdigit(c))
            tmp_mantiss[count++] = c;
        else if (c == '\n' && count  == 0) {
            tmp_mantiss[count++] = '0';
            break;
        }
        else if (c == '\n')
            break;
        else
            return 3;
    }
    while ((c = getchar()) != EOF);
    tmp_mantiss[count] ='\0';
    tmp_len = strlen(tmp_mantiss);
    for (int i = tmp_len - 1; i >= 0; i--)
        a->mantissa_field[MANTISSA_LEN - (tmp_len - i)] = tmp_mantiss[i];

    return 0;
}
/* Выбивает по длине строки */
int sbigfloat_scanf(bignum_t *a)
{
    int c;
    int count = 0;
    size_t first_digit = MANTISSA_LEN_FLOAT - 1;
    size_t f_float = 0;
    int tmp_order = 0, count_zero = 0;
    long order = 0;
    int neg_order = 0;

    // del lead zeros
    for(size_t i = 0; (c = getchar()) != EOF && i < MAX_LEN_INPUT_STR; i++) {
        if (c == '-') {
            a->is_negative = 1;
            continue;
        }
        else if (c == '0' && f_float) {
            tmp_order--;
            count_zero++;
            continue;
        }
        else if (c == '0')
            continue;
        else if (c == '.' && f_float) {
            return 1;
        }  
        else if (c == '.') {
            f_float = 1;
            continue;
        }  
        else if (isdigit(c)) {
            a->mantissa_field[first_digit] = c;
            first_digit -= 1;
            count++;
            break;
        }
        else if (c == '\n')
            break;
        else if (isspace(c) || c == 'E')
            break;
        else
            return 2;
    }
    if (c == '\n')
        return 0;
    // scanf mantiss
    for (int j = first_digit; j >= 0 && (c = getchar()) != EOF;) {
        if (isdigit(c)) {
            count++;
            a->mantissa_field[j--] = c;
        }
        else if (c == '.' && f_float) {
            return 3;
        }  
        else if (c == '.') {
            tmp_order = MANTISSA_LEN_FLOAT - j - 1;
            f_float = 1;
        }
        else if (c == '\n')
            return 4;
        else if (isspace(c) || c == 'E') {
            break;
        }
        else
            return 5;
    }
    if (isdigit(c = getchar()))
        return 6;
    int flag = 0;
    do {
        if (c == '\n')
            break;
        else if (isspace(c) || c == 'E' )
            continue;
        else if (c == '-' && flag)
            return 7;
        else if (c == '-') {
            neg_order = 1;
            flag = 1;
        }
        else if (isdigit(c)) {
            order = order * 10 + (c - '0');
            flag = 1;
        }
        else
            return 8;
    } while ((c = getchar()) != EOF);

    if (neg_order)
        order = -order;

    if (order > MAX_ORDER)
        return 9;
    if (order < MIN_ORDER)
        return 10;

    f_float ? (order += tmp_order) : (order += count);    
    a->order = order;
    for (size_t t = 0; t < MANTISSA_LEN_FLOAT && (a->mantissa_field[t] == 0 || a->mantissa_field[t] == '0'); t++)
        if (a->mantissa_field[t] == '0') {
            a->mantissa_field[t] = 0;
        }

    revers_num(a->mantissa_field, MANTISSA_LEN_FLOAT);
    return 0;
}


int is_null(unsigned char *a, size_t alen)
{
    for (size_t i = 0; i < alen; i++)
        if (a[i] != 0 && a[i] != '0')
            return 0;
    return 1;
}
// 0000000012340 -> 5
size_t len_mantiss(unsigned char *str, size_t max_len)
{
    size_t len = 0;
    for (size_t i = 0; i < max_len; i++)
        if (str[i] == '0' || str[i] == 0) {
            len++;
            continue;
        }
        else if (isdigit(str[i]))
            break;

    return max_len - len;
}

int bignum_add_field(unsigned char *dst, unsigned char *src, size_t len)
{
    int summ;
    size_t transfer = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (dst[i] == 0 && src[i] == 0 && transfer) {
            summ = transfer;
            transfer = 0;
        }
        else if (dst[i] == 0)
            summ = src[i] - '0' + transfer;
        else if (src[i] == 0)
            summ = dst[i] - '0' + transfer;
        else
            summ = (dst[i] - '0') + (src[i] - '0') + transfer;

        if (summ > 9) {
            dst[i] = '0' + summ % 10;
            transfer = summ / 10;
        }
        else {
            dst[i] = '0' + summ;
            transfer = 0;
        }
    }
    if (transfer)
        return 1;
    return 0;
}

/* Пользователь гарантирует, что есть место для сдвига */
int append_zero(unsigned char *a, int alen, size_t count_zero)
{
    if (count_zero == 0)
        return 0;
    int i = 0;
    while (i < alen && a[i] == 0)
        i++;
    int j = i - count_zero;
    if (j < 0)
        return ERROR_OWERFLOW_MANTISSA;

    for (; j < alen; j++, i++)
        if (i < alen) {
            a[j] = a[i];
            a[i] = '0';
        }
        else
            a[j] = '0';
    return 0;
}

int bignum_field_mul_digit(unsigned char *dst, unsigned char *src, size_t maxlen, int digit)
{
    int summ;
    size_t transfer = 0;
    int i = maxlen - 1;
    for (; i >= 0; i--) {
        if (src[i] == 0) {
            summ = transfer;
            transfer = 0;
        }
        else
            summ = (src[i] - '0') * digit + transfer;
        if (summ > 9) {
            dst[i + MANTISSA_LEN_FLOAT] = '0' + summ % 10;
            transfer = summ / 10;
        }
        else {
            dst[i + MANTISSA_LEN_FLOAT] = '0' + summ;
            transfer = 0;
        }
    }
    if (transfer) {
        dst[i + MANTISSA_LEN_FLOAT] = '0' + transfer;
    }
    return 0;
}

int bignum_round(unsigned char *dst, int dlen, unsigned char *src, int slen, int len_mantiss)
{
    int summ;
    size_t transfer = 0;
    int i = slen - 1;
    // printf("ZZZZZZ");
    // printf("i = %d, max_i = %d\n", slen - 1, slen - (len_mantiss - MANTISSA_LEN) - 1);
    // считаем трансфер после 40-й цифры
    for (; i > slen - (len_mantiss - MANTISSA_LEN) - 1; i--) {
        if (src[i] == 0) {
            summ = transfer;
            transfer = 0;
            break;
        }
        else if ((summ = src[i] - '0' + transfer) >= 5)
            transfer = 1;
        else
            transfer = 0;
    }   
    // printf("tran = %zu\n", transfer);
        // if (summ > 9)
        //     dst[i + MANTISSA_LEN_FLOAT] = '0' + summ % 10;
        // else
        //     dst[i + MANTISSA_LEN_FLOAT] = '0' + summ;

    
    // printf("sum = %zu i=%d\n", transfer, i);
    int t = dlen; 
    for (; i >= 0 && !transfer; i--, t--) {
        // printf("%c/", src[i]);
        dst[t] = src[i];
        // printf("%c", dst[t]);
    }
    // for (int i = 0; i < dlen; i++)
    //     printf("%c(", dst[i]); 
    // printf("source\n");
    int tmp_count = 0;
    for (int t = dlen - 1; t > 0 && dst[t] == '0'; t--, tmp_count++)
        ;
    for (int k = dlen - 1; k >= tmp_count; k--)
        dst[k] = dst[k - tmp_count];
    // for (int l = 0; l < dlen; l++) {
     
    //     printf("%c}", dst[l]);
    // }
    // printf("ertyui\n");
    for (int p = 0; p < tmp_count; p++)
        dst[p] = 0;
    // for (int i = 0; i < slen; i++)
    //     printf("%c|", src[i]); 
    // printf("source\n");
    // printf("round\n");
    // for (int i = 0; i < dlen; i++)
    //     printf("%c|", dst[i]); 
    // printf("round\n");
    for (; i > 0 && transfer; i--) {
        // printf("%d\n", i);
        if (src[i] == 0) {
            summ = transfer;
            transfer = 0;
            break;
        }
        else if ((summ = src[i] - '0' + transfer) >= 5)
            transfer = 1;
        else
            transfer = 0;
        // printf("%d\n", i);
        // printf("sum = %d\n", summ);
        if (summ > 9)
            dst[i] = '0' + summ % 10;
        else
            dst[i] = '0' + summ;
        // printf("%d\n", i);
    }
    // for (int i = 0; i < dlen; i++)
    //     printf("%c/", dst[i]); 
    // printf("%c %c\n", dst[MANTISSA_LEN - 2], dst[MANTISSA_LEN - 1]);
    // printf("%s\n", dst);
    // Округление до 1
    // printf("YYY&");
    if (transfer) {
        for (int j = 0; j < dlen; j++)
            dst[j] = 0;
        // printf("YYY");
        dst[dlen - 1] = '0' + transfer;
        transfer = 0;
    }

    // printf("round\n");
    // for (int i = 0; i < dlen; i++)
    //     printf("%c/", dst[i]); 
    // printf("round\n");
    // del non-significant zeros and change order
    int count = 0;
    for (int t = dlen - 1; t > 0 && dst[t] == '0'; t--, count++)
        ;
    for (int k = dlen - 1; k > count; k--)
        dst[k] = dst[k - count];
    return 0;
}
/* В случае успеха возвращает 0, иначе не ноль 
    целое (40) на действительное (30) */
int bignum_mul(bignum_t *a, bignum_t *b, bignum_t *res)
{
    unsigned char buf_mul[MANTISSA_LEN + MANTISSA_LEN_FLOAT] = {0};
    unsigned char summ[MANTISSA_LEN + MANTISSA_LEN_FLOAT] = {0};
    unsigned char round_buf[MANTISSA_LEN] = {0};
    int len_summ;
    for (size_t i = MANTISSA_LEN_FLOAT - 1; i >= MANTISSA_LEN_FLOAT - len_mantiss(b->mantissa_field, MANTISSA_LEN_FLOAT); i--) {
        if (b->mantissa_field[i] == 0)
            break;
        if (bignum_field_mul_digit(buf_mul, a->mantissa_field, MANTISSA_LEN, b->mantissa_field[i] - '0'))
            return 1;
        for (size_t t = 0; t < MANTISSA_LEN + MANTISSA_LEN_FLOAT && (buf_mul[t] == 0 || buf_mul[t] == '0'); t++)
            if (buf_mul[t] == '0') {
                buf_mul[t] = 0;
            }
        if (append_zero(buf_mul, MANTISSA_LEN + MANTISSA_LEN_FLOAT, MANTISSA_LEN_FLOAT - (i + 1)))
            return 2;
        if (bignum_add_field(buf_mul, summ, MANTISSA_LEN + MANTISSA_LEN_FLOAT))
            return 3;
        for (int i = 0; i < MANTISSA_LEN + MANTISSA_LEN_FLOAT; i++) {
            summ[i] = buf_mul[i];
            buf_mul[i] = 0;
        }
    }
    if ((!a->is_negative && b->is_negative) || 
        (a->is_negative && !b->is_negative))
        res->is_negative = 1;
    len_summ = len_mantiss(summ, MANTISSA_LEN + MANTISSA_LEN_FLOAT);
    int tmp_count = 0;
    for (int t = MANTISSA_LEN + MANTISSA_LEN_FLOAT - 1; t > 0 && summ[t] == '0'; t--, tmp_count++)
        ;
    for (int k = MANTISSA_LEN + MANTISSA_LEN_FLOAT - 1; k >= tmp_count; k--)
        summ[k] = summ[k - tmp_count];
    
    int len_clean_mantiss = len_mantiss(summ, MANTISSA_LEN + MANTISSA_LEN_FLOAT);
    if (len_clean_mantiss > 40) {
        bignum_round(round_buf, MANTISSA_LEN, summ, MANTISSA_LEN + MANTISSA_LEN_FLOAT, len_clean_mantiss);
        for (int i = 0; i < MANTISSA_LEN; i++)
            res->mantissa_field[i] = round_buf[i];
    }
    else
    {
        for (int i = 0; i < MANTISSA_LEN; i++)
            res->mantissa_field[i] = summ[MANTISSA_LEN_FLOAT + i];
    }

    res->order = len_summ + (b->order - len_mantiss(b->mantissa_field, MANTISSA_LEN_FLOAT));
    
    if (res->order > MAX_ORDER)
        return 5;
    if (res->order < MIN_ORDER)
        return 6;

    return 0;
}
