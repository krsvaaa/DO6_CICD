#!/bin/bash


cd ./src/cat
./test_cat.sh > test_cat_output.txt
cat test_cat_output.txt | grep "fail - 0" > cat_grep_fail.txt

if [ -s "cat_grep_fail.txt" ]; then
	echo "cat:"
	cat cat_grep_fail.txt

	cd ../grep
	./test_grep.sh > test_grep_output.txt
	cat test_grep_output.txt | grep "fail - 0" > grep_grep_fail.txt
	if [ -s "grep_grep_fail.txt" ]; then
		echo "grep:"
		cat grep_grep_fail.txt
		echo "Test success"
		exit 0
	else
		echo "Test fail"
		exit 1
	fi
else
	echo "Test fail"
	exit 1
fi
