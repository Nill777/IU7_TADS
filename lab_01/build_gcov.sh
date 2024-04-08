#!/bin/bash

# Компиляция
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -c -g3 --coverage main.c my_strfunc.c

# Комановка(-o название исполняемого файла)
gcc -o main_gcov.exe main.o my_strfunc.o --coverage -lm