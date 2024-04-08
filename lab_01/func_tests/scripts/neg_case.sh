#!/bin/bash

# Все делаем из папки lab_!!!
# Проверка количества переданных файлов
if [ $# -ne 2 ]; then
	exit 1
fi

file_in=$1
file_args=$2

# Коды ошибок
test_pass="0"
test_failed="1"

flag=$(head -n 1 "$file_args")
file_substr=$(sed '2q;d' "$file_args")

# Если передали входной и выходной файлы,
# то передаём их исполняемому файлу *.exe

touch ./func_tests/scripts/prog_neg.out
prog="./func_tests/scripts/prog_neg.out"


if [[ -z "$file_substr" ]]; then
	command="./*.exe ${file_in} ${flag}"
	$command > "$prog"
else
	command="./*.exe ${file_in} ${flag} ${file_substr}"
	$command > "$prog"
fi
return_code="$?"
echo "return code ""$return_code"
# Проверка завершения программы
if [ "$return_code" -ne 0 ]; then						# не нулевой код ошибки возврата
	exit "$test_pass"									# верный тест
else
	exit "$test_failed"									# неверный тест
fi
