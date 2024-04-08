#!/bin/bash

# *.txt *.exe *.o *.out *.gcno *.gcda *.gcov
junk_files1="./func_tests/scripts/*.out"
junk_files2="./*.exe *.o *.gcno *.gcda *.gcov"
# Проверить, существует ли файл
for el in $junk_files1 $junk_files2;
do
    if [[ -f $el ]]; then
        rm "$el"
        #echo "Мусорный файл $el удален"
    fi
done