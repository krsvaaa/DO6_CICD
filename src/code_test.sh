#!/bin/bash


cd cat
./test_cat.sh > test_cat_output.txt
cat test_cat_output.txt | grep "fail - 0" > cat_ok.txt

if [ -s "cat_ok.txt" ]; then
	echo "cat:"
	cat cat_ok.txt

	cd ../grep
	./test_grep.sh > test_grep_output.txt
	cat test_grep_output.txt | grep "fail - 0" > grep_ok.txt
	if [ -s "grep_ok.txt" ]; then
		echo "grep:"
		cat grep_ok.txt
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
