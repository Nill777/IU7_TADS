#!/bin/bash

# Все делаем из папки lab_!!!
# Проверка количества аргументов
if [ $# -ne 3 ]; then
    exit 1
fi

file_in=$1
file_out=$2
file_args=$3

# Коды ошибок
test_pass="0"
test_failed="1"

# args=$(head -n 1 "$file_args")
# substr=$(sed '2q;d' "$file_args")
# cur_substr=$(sed '3q;d' "$file_args")

# echo "$args"
# echo "$substr"
# echo "$cur_substr"
# Если передали входной и выходной файлы,
# то передаём их исполняемому файлу *.exe

touch ./func_tests/scripts/prog_pos.out
prog="./func_tests/scripts/prog_pos.out"

# if [[ -z "$cur_substr" ]]; then
command="./*.exe $(cat "$file_args")"
$command > "$prog"
# else
# 	command="./*.exe ${args} ${substr} ${cur_substr}"
# 	$command > "$prog"
# 	# ./*.exe ${file_in} ${flag} ${file_substr} > "$prog"
# 	# echo "$?"
# 	# echo "./*.exe ${file_in} ${flag} ${file_substr} > "$prog""
# fi
return_code="$?"

# cat $prog
# cat $file_out
# echo "return code ""$return_code"
# Проверка завершения программы
if [ "$return_code" -ne 0 ]; then						# не нулевой код ошибки
	exit "$test_failed"
fi

# сравниваем выходные данные программы и данные в тесте
if sh ./func_tests/scripts/comparator.sh "$prog" "$file_out"; then					# верный тест
	
    exit "$test_pass"
else							# неверный тест
	exit "$test_failed"
fi
