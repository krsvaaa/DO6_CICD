#1/bin/bash

clang-format -style=google -n *.c *.h 2> clang_output.txt

if [ -s "clang_output.txt" ]; then
	cat clang_output.txt
	exit 1
else
	exit 0
fi

