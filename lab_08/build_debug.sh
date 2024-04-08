#!/bin/bash
#  -Wvla
# Компиляция
gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -c -g3 main.c graph.c

# Комановка(-o название исполняемого файла)
gcc -o app.exe main.o graph.o -lm