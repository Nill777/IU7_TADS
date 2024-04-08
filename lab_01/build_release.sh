#!/bin/bash

# Компиляция
gcc -std=c99 -c main.c bignum.c

# Комановка
gcc -o main_release.exe main.o bignum.o -lm
