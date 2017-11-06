#!/bin/sh

./start.sh

../bin/rshell < inputs/multi_input.txt > multi_output.txt
echo -e "\n" >> multi_output.txt

if cmp -s multi_output.txt expects/multi_expect.txt; then
    echo Tests Passed!
else
    echo Tests Failed!
    diff multi_output.txt expects/multi_expect.txt
fi

./clean.sh
