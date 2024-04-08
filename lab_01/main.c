#include <stdio.h>
#include <string.h>
#include "bignum.h"
// #include "constants.h"

int main(void)
{
    int rc;
    bignum_t a, b, res;
    bignum_init(&a);
    bignum_init(&b);
    bignum_init(&res);

    printf("Программа осуществляет умножение целого чисела на действительное \n"
            "с длиной мантиссы целого до 40 знаков и действительного до 30 с порядком до 5 знаков.\n"
            "Введите целое число в формате +-m, \n"
            "где длина мантиссы m - до 40 значащих цифр:\n");
    printf("----|----1----|----2----|----3----|----4----|----5\n");
    if ((rc = sbigint_scanf(&a)))
    {
        printf("Ошибка ввода первого числа, типа %d\n", rc);
        return ERROR_INPUT_FIRST;
    }

    printf("Введите действительное число в формате +-m.n Е +-K, \n"
            "где суммарная длина мантиссы (m+n) - до 30 значащих цифр, а величина порядка K - до 5 цифр:\n");
    printf("----|----1----|----2----|----3----|----4----|----5\n");
    if ((rc = sbigfloat_scanf(&b)))
    {
        printf("Ошибка ввода второго числа, типа %d\n", rc);
        return ERROR_INPUT_SECOND;
    }
    if (is_null(a.mantissa_field, MANTISSA_LEN) || is_null(b.mantissa_field, MANTISSA_LEN_FLOAT)) {
        printf("----|----1----|----2----|----3----|----4----|----5\n");
        printf("0.0 E 0\n");
        return 0;
    }

    if ((rc = bignum_mul(&a, &b, &res)))
    {
        printf("Ошибка умножения, типа %d\n", rc);
        return ERROR_MUL;
    }

    printf("----|----1----|----2----|----3----|----4----|----5\n");
    bigfloat_print(&res);
    printf("\n");

    return 0;
}
