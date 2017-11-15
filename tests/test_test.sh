#!/bin/sh

./start.sh

../bin/rshell < inputs/test_input.txt > test_output.txt
echo -e "\n" >> test_output.txt

if cmp -s test_output.txt expects/test_expect.txt; then
    echo Tests Passed!
else 
    echo Tests Failed!
    diff test_output.txt expects/test_expect.txt
fi

./clean.sh
