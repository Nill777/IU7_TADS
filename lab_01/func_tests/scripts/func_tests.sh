#!/bin/bash

# Количество ошибочных тестов
count_err=0
pos=0
neg=0

# Коды ошибок
test_pass="0"

# Позитивные тесты
files="./func_tests/data/pos_??_in.txt"
for file_in in $files; do

	# Вытаскиваем номер теста
	number=$(echo "$file_in" | grep -o "[0-9]*")

	# Проверка на наличие тестов(-z длина строки = 0)
	if [ -z "$number" ]; then
		break
	fi
	# Флаг наличия поз. тестов
    pos=1

	# Название выходного тестового файла
	file_out="./func_tests/data/pos_""$number""_out.txt"
	# Название файла с аргументами
	# file_args="./func_tests/data/pos_""$number""_args.txt"

	# Выходной файл существует => передаем входной и выходной файлы в pos_case.sh
	# Не существует, то тест провален, переходим к следующему тесту

	if [ -f "$file_out" ]; then
		command="sh ./func_tests/scripts/pos_case.sh ""$file_in ""$file_out "
	else
		echo -e "\033[31mPOS_""$number"": FAILED\033[0m"
		count_err=$((count_err + 1))
		continue
	fi

	$command
	return_code="$?"

	# Результат в соответствии с кодом возврата ./pos_case.sh
	if [ "$return_code" = "$test_pass" ]; then
		echo -e "\033[32mPOS_""$number"": PASSED\033[0m"
	fi
	if [ "$return_code" != "$test_pass" ]; then
		echo -e "\033[31mPOS_""$number"": FAILED\033[0m"
		count_err=$((count_err + 1))
        pos=$((pos + 1))
	fi

done

# Негативные тесты 
files="./func_tests/data/neg_??_in.txt"
for file_in in $files; do

	# находим номер теста
	number=$(echo "$file_in" | grep -o "[0-9]*")

	# проверка на наличие тестов(-z длина строки = 0)
	if [ -z "$number" ]; then
		break
	fi
	# Флаг наличия нег. тестов
    neg=1

	# Название файла с аргументами
	# file_args="./func_tests/data/neg_""$number""_args.txt"
	# Передаем входной тестовый файл в ./neg_case.sh
	command="sh ./func_tests/scripts/neg_case.sh ""$file_in "
	
	$command
	return_code="$?"

	# Результат в соответствии с кодом возврата ./neg_case.sh
	if [ "$return_code" = "$test_pass" ]; then
		echo -e "\033[32mNEG_""$number"": PASSED\033[0m"
	fi
	if [ "$return_code" != "$test_pass" ]; then
		echo -e "\033[31mNEG_""$number"": FAILED\033[0m"
		count_err=$((count_err + 1))
	fi
done

# Дополнительная информация

if [ "$count_err" = 0 ]; then
	echo "All tests passed." 
else
	echo "Failed $count_err tests." 
fi

if [ "$pos" = 0 ]; then
	echo "No positive tests." 
fi

if [ "$neg" = 0 ]; then 
	echo "No negative tests."
fi

exit "$count_err"
