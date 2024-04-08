#!/bin/bash

# Компиляция
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -c -g3 main.c bignum.c

# Комановка(-o название исполняемого файла)
gcc -o main_debug.exe main.o bignum.o -lm