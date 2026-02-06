#!/bin/bash
make all

flags=("-e" "-i" "-v" "-c" "-l" "-n")
files=("./tests_grep/1.txt" "./tests_grep/2.txt" "./tests_grep/3.txt" "./tests_grep/4.txt" "./tests_grep/5.txt")
templates=("art" "wisdom" "monke" "123" "HILL" "HEllo" "match")

s_count=0
f_count=0

for flag in "${flags[@]}"
do
    test_number=1
    echo " "
    echo "Flags: $flag"
    for template in "${templates[@]}"
    do
        for test_file in "${files[@]}"
        do
            echo "Pattern: $template in File: $test_file"
            ./s21_grep $flag "$template" "$test_file" > a.txt
            grep $flag "$template" "$test_file" > b.txt
            if ! cmp -s a.txt b.txt; then
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
                echo "Pattern: $template (2 files) Files: $test_file1 $test_file2"
                ./s21_grep $flag $template $test_file1 $test_file2 > a.txt
                grep $flag $template $test_file1 $test_file2 > b.txt
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
done

echo "fail - $f_count"
echo "success - $s_count"
rm a.txt b.txt

