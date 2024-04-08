#!/bin/bash
#  -Wvla
# Компиляция
gcc -std=c99 -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -c -g3 main.c func.c

# Комановка(-o название исполняемого файла)
gcc -o app.exe main.o func.o -lm