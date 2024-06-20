#!/bin/bash

TESTS_OUT=tests-out
TESTS=tests
NUM_TESTS=4

if [ ! -d ${TESTS_OUT} ]
then
    mkdir ${TESTS_OUT}
fi

# Cleanup the previous run's temporary files
rm -f ${TESTS_OUT}/*.out

# Run tests
total=0
for task_no in `seq 1 ${NUM_TESTS}`
do
    exe="task${task_no}"
    echo -e "\n=====\nRunning tests for ${exe}\n=====\n"

    task_tests="${TESTS}/t${task_no}"

    # Account for extra points in bouns tasks
    test_points=1
    if [ ${task_no} -gt 2 ]
    then
        test_points=4
    fi

    for i in `ls -v ${task_tests}`
    do
        in_file="${task_tests}/$i"
        if [ -f ${in_file} ]
        then
            #echo "i = $i"
            #echo "in_file = ${in_file}"

            #echo "Starting test $i"
            #echo "out = ${TESTS_OUT}/$i.out"

            # Ensure files are ASCII
            #x=$(cat ${in_file})
            #echo "$x" > ${in_file}

            ./${exe} < ${in_file} > ${TESTS_OUT}/$i.out
            #echo "Finished test $i"

            ref_file="r${i:1}"
            ref_dir="${task_tests}/ref_output"
            #echo "ref = ${TESTS}/ref_output/${ref_file}"

            # Ensure files are ASCII
            #x=$(cat "${ref_dir}/${ref_file}")
            #echo "$x" > "${ref_dir}/${ref_file}"

            diff ${TESTS_OUT}/$i.out ${ref_dir}/${ref_file} > /dev/null
            if [ $? -eq 0 ]
            then
                echo "TEST $i PASSED"
                total=$((total + test_points))
            else
                echo "TEST $i FAILED"
            fi
        fi
    done
done

echo "TOTAL ${total}"
