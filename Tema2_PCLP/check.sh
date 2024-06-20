#!/bin/bash

EXEC="tema2"

function init {
	total_score=0
	pad=$(printf '%.1s' "."{1..70})
	padlength=71

	make
	if [ $? -ne 0 ]; then
		echo "Makefile failed!"
		exit 1
	fi

	
	mkdir -p output/Task1
	mkdir -p output/Task2
	mkdir -p output/Task3
	mkdir -p output/Task4
	mkdir -p output/Task5
}

function print_result {
	printf "%s" "$1"
	printf "%*.*s" 0 $((padlength - ${#1} - ${#2} )) "$pad"
	printf "%s\n" "$2"
}

function check_task {
	task_id=$1
	start_test_id=$2
	end_test_id=$3
	test_score=$4
	echo "..............................TASK $task_id..................................."

	for test_id in $(seq $start_test_id $end_test_id); do
		test_file="./input/Task${task_id}/input${test_id}.txt"
        ref_file="./ref/Task${task_id}/ref${test_id}.txt"
        output_file="./output/Task${task_id}/output${test_id}.txt"

		if [ $task_id == 3 ]; then
			grep 'qsort(' task3.c &>/dev/null
			if [ ! $? -eq 0 ]; then
				echo "!!!!!!!!!!!!!!!!!!!!!!!!!! PLEASE USE QSORT !!!!!!!!!!!!!!!!!!!!!!!!!!!"
				print_result "Test ${test_id}" "0/${test_score}p failed"
				continue
			fi
		fi
	
		./$EXEC < "$test_file" > "$output_file"
	
		if [ -f "$output_file" ]; then
			if diff -w "$output_file" "$ref_file" &> /dev/null; then
				let "total_score += $test_score"
				print_result "Test ${test_id}" "${test_score}/${test_score}p passed"
			else 
				print_result "Test ${test_id}" "0/${test_score}p failed"
			fi
		fi
		# rm -f "$output_file"
	done

    echo " "
}

function check_readme {
	echo "..............................TASK README.............................."
    
	ls . | grep -i "readme" &>/dev/null
	if [ $? -eq 0 ]; then
		print_result "Test README" "10/10p passed"
		let "total_score += 10"
	else
		print_result "Test README" "0/10p failed"
	fi
    echo " "
}

function check_style {
	is_style_ok=1
	echo -e "\nRun cpplint\n" > result
#	cpplint --filter=-legal/copyright task1.c task2.c task3.c task4.c tema2.c &>> result
	cpplint --filter=-legal/copyright,-readability/casting,-build/include_subdir,-runtime/threadsafe_fn,-build/header_guard,-runtime/int \
        --linelength=120 $( find . -name \*.h -or -name \*.c ) &>> result
if [ ! $? -eq 0 ]
then
    is_style_ok=0
fi

	echo -e "\nRun clang-tidy\n" >> result
#	clang-tidy  -checks='-*,cppcoreguidelines*' task1.c task2.c task3.c task4.c tema2.c -- &>> result
clang-tidy -checks='-*,cppcoreguidelines*' --warnings-as-errors='-*,cppcoreguidelines*' $( find . -name \*.h -or -name \*.c ) -- &>> result
if [ ! $? -eq 0 ]
then
    is_style_ok=0
fi

if [ $is_style_ok -eq 0 ]
then
    print_result "Test Coding Style" "-10/0p failed"
    let "total_score -= 10"
else
    print_result "Test Coding Style" "0/0p passed"
fi
	# Display run summary
	awk -f parse.awk result

	# Display detailed report
	echo -e "\n==================="
	echo -e "= Detailed report ="
	echo -e "===================\n"
	cat result
	echo " "
	echo " "
}


init
check_task 1 1 5 4 # task1, test0-4, score per test = 4 - 20 pct
check_task 2 1 5 4 # task2, test0-4, score per test = 4 - 20 pct
check_task 3 1 5 10 # task3, test0-4, score per test = 10 - 50 pct
check_task 4 1 5 10 # task4, test0-4, score per test = 10 - 50 pct
check_task 5 1 5 10 # task4, test0-4, score per test = 10 - 50 pct
check_readme # 10 pct

# PENTRU VERIFICARE CODINGSTYLE DECOMENTATI URMATOAREA LINIE
check_style

print_result "Final score" "${total_score}/200"
make clean &> /dev/null

if [ $total_score == 200 ]; then
	echo " "
	echo " "
	echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! GOOD JOB !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
	mpg123 -vC "Rick Astley - Never Gonna Give You Up.mp3" &> /dev/null
fi
