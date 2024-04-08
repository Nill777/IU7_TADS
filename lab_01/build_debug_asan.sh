#!/bin/bash

clang -std=c99 -Wall -fsanitize=address -fno-omit-frame-pointer -g main.c bignum.c -o main_asan.exe
