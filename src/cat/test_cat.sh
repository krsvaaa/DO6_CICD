#!/bin/bash
make all

flags=("-b" "-e" "-E" "-n" "-s" "-t" "-T" "--number-nonblank" "--number" "--squeeze-blank")
files=("./tests_cat/1.txt" "./tests_cat/2.txt" "./tests_cat/3.txt" "./tests_cat/4.txt" "./tests_cat/5.txt")

s_count=0
f_count=0

for flag in "${flags[@]}"
do
    test_number=1
    echo " "
    echo "Flags: $flag:"
    for test_file in "${files[@]}"
    do
        ./s21_cat $flag $test_file > a.txt
        cat $flag $test_file > b.txt
        if ! cmp -s a.txt b.txt ; then
            echo "Test $test_number: Fail"
            f_count=$((f_count + 1))
        else
            echo "Test $test_number: Success"
            s_count=$((s_count + 1))
        fi
        
        test_number=$((test_number + 1))
        
        ./s21_cat $test_file $flag > a.txt
        cat $test_file $flag > b.txt
        if ! cmp -s a.txt b.txt ; then
            echo "Test $test_number: Fail"
            f_count=$((f_count + 1))
        else
            echo "Test $test_number: Success"
            s_count=$((s_count + 1))
        fi
        
        test_number=$((test_number + 1))
    done

    for ((i=0; i<${#files[@]}; i++))
    do
        for ((j=i+1; j<${#files[@]}; j++))
        do
            test_file1=${files[$i]}
            test_file2=${files[$j]}
            echo "Files: $test_file1 $test_file2"
            ./s21_cat $flag $test_file1 $test_file2 > a.txt
            cat $flag $test_file1 $test_file2 > b.txt
            if ! cmp -s a.txt b.txt; then
                echo "Test $test_number: Fail"
                f_count=$((f_count + 1))
            else
                echo "Test $test_number: Success"
                s_count=$((s_count + 1))
            fi
            test_number=$((test_number + 1))
        done
    done
done

echo "fail - $f_count"
echo "success - $s_count"
rm a.txt b.txt

