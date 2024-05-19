#!/bin/bash

function init {
    total_score=0
    pad=$(printf '%.1s' "."{1..70})
    padlength=71

    TESTS_OUT=tests-out
    TESTS=tests
    NUM_TESTS=10

    if [ ! -d ${TESTS_OUT} ]
    then
        mkdir ${TESTS_OUT}
    fi

    # Cleanup the previous run's temporary files
    rm -f ${TESTS_OUT}/*.out
}

function print_result {
    printf "%s" "$1"
    printf "%*.*s" 0 $((padlength - ${#1} - ${#2} )) "$pad"
    printf "%s\n" "$2"
}

function check_task {
    # check_task(task_no, exe_name, test_score)
    echo "................................TASK $1................................."
    exe=$2
    TASK_TESTS="${TESTS}/$2"
    TASK_TESTS_OUT="${TESTS_OUT}/$2"
    test_score=$3

    mkdir -p ${TASK_TESTS_OUT}

    for (( i = 0; i < ${NUM_TESTS}; ++i))
    do
        in_file="${TASK_TESTS}/input/f_$i.in"
        ref_file="${TASK_TESTS}/ref_output/f_$i.out"
        out_file="${TASK_TESTS_OUT}/$i.out"

        test_id=$i

        ./${exe} < ${in_file} > ${out_file}

        diff ${out_file} ${ref_file} > /dev/null
        if [ $? -eq 0 ]
        then
            let "total_score += $test_score"
            print_result "Test ${test_id}" "${test_score}/${test_score}p passed"
        else
            print_result "Test ${test_id}" "0/${test_score}p failed"
        fi
    done
}

function check_readme {
    echo -e "\n..............................TASK README.............................."

    ls . | grep -i "readme" &>/dev/null
    if [ $? -eq 0 ]; then
        print_result "Test README" "0/0p passed"
    else
        print_result "Test README" "-$1/0p failed"
        let "total_score -= $1"
    fi
}

function check_style {
    echo -e "\n..............................CODING STYLE............................."
    is_style_ok=1
    echo -e "\nRun cpplint\n" > result
    cpplint --filter=-legal/copyright,-readability/casting,-build/include_subdir,-runtime/threadsafe_fn,-build/header_guard,-runtime/int \
        --linelength=120 $( find . -name \*.h -or -name \*.c ) &>> result

    if [ ! $? -eq 0 ]; then
        is_style_ok=0
    fi

    echo -e "\nRun clang-tidy\n" >> result
    clang-tidy -checks='-*,cppcoreguidelines*' --warnings-as-errors='-*,cppcoreguidelines*' $( find . -name \*.h -or -name \*.c ) -- &>> result

    if [ ! $? -eq 0 ]; then
        is_style_ok=0
    fi

    if [ $is_style_ok -eq 0 ]; then
        print_result "Test Coding Style" "-20/0p failed"
        let "total_score -= 20"
    else
        print_result "Test Coding Style" "0/0p passed"
    fi

    # Display run summary
    awk -f parse.awk result

    # Display detailed report
    echo -e "\n================================"
    echo -e "= Detailed coding style report ="
    echo -e "================================\n"
    cat result
    echo " "
    echo " "
}

function run_checker {
    init
    check_task 1 task1 5 # task_no=1, exe_name=task1, test_score=5 - total=50 pct
    check_task 2 task2 5 # task_no=2, exe_name=task2, test_score=5 - total=50 pct
    check_task 3 task3 5 # task_no=1, exe_name=task1, test_score=5 - total=50 pct
    check_readme 10 # 10 pct
    check_style

    print_result "Final score" "${total_score}/150"
}

TIMEOUT_VAL=1

export -f run_checker init check_task check_readme check_style print_result
#timeout ${TIMEOUT_VAL} run_checker
#timeout ${TIMEOUT_VAL} bash <<EOT
#run_checker
#EOT
run_checker

if [ ! $? -eq 0 ]
then
    echo "TIMEOUT. Tests exceeded maximum allowed time of $TIMEOUT_VAL"
fi

