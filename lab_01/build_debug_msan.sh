#!/bin/bash

clang -std=c99 -Wall -fsanitize=memory -fno-omit-frame-pointer -g main.c bignum.c -o main_msan.exe
