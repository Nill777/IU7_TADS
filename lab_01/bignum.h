#ifndef BIGNUM_H
#define BIGNUM_H

#include "constants.h"

/* Храним мантису в обратном порядке 
          порядок в прямом с лидирующими нулями
*/
typedef struct {
    unsigned char is_negative;
    unsigned char mantissa_field[MANTISSA_LEN];
    long int order;
} bignum_t;

void bignum_init(bignum_t *a);

void bignum_print_field(unsigned char *a, size_t alen);
void bigint_print(bignum_t *a);
void bigfloat_print(bignum_t *a);
void bigres_print(bignum_t *a);

void revers_num(unsigned char *a, size_t alen);
int sbigint_scanf(bignum_t *a);
int sbigfloat_scanf(bignum_t *a);
int is_null(unsigned char *a, size_t alen);
size_t len_mantiss(unsigned char *str, size_t max_len);

// int bignum_cmp_field(unsigned char *a, unsigned char *b, size_t len);
// int bignum_cmp(bignum_t *a, bignum_t *b);



int bignum_add_field(unsigned char *dst, unsigned char *src, size_t len);
int append_zero(unsigned char *a, int alen, size_t count_zero);
int bignum_field_mul_digit(unsigned char *dst, unsigned char *src, size_t maxlen, int digit);
int bignum_round(unsigned char *dst, int dlen, unsigned char *src, int slen, int len_mantiss);
int bignum_mul(bignum_t *a, bignum_t *b, bignum_t *res);

#endif
