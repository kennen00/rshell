#!/bin/sh

./start.sh

../bin/rshell < inputs/commented_input.txt > commented_output.txt
echo -e "\n" >> commented_output.txt

if cmp -s commented_output.txt expects/commented_expect.txt; then
    echo Tests Passed!
else 
    echo Tests Failed!
    diff commented_output.txt expects/commented_expect.txt
fi

./clean.sh
