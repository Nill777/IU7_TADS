#!/bin/bash

clang -std=c99 -Wall -fsanitize=undefined -fno-omit-frame-pointer -g main.c bignum.c -o main_udsan.exe
