#!/bin/bash

# Проверка количества аргументов
if [ $# -ne 2 ]; then
    exit 1
fi

out_prog=$1
out_test=$2
# cat $out_prog
# echo "---------------"
# cat $out_test
# сравниваем их
# if cmp -s "$out_prog" "$out_test"; then
#     echo "одинаковые"
# else
#     echo "разные"
# fi
if cmp -s "$out_prog" "$out_test"; then
    exit 0
fi
exit 1