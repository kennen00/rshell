#!/bin/sh

./start.sh

../bin/rshell < inputs/single_input.txt > single_output.txt
echo -e "\n" >> single_output.txt

if cmp -s single_output.txt expects/single_expect.txt; then
    echo Tests Passed!
else
    echo Tests Failed!
    diff single_output.txt expects/single_expect.txt
fi

./clean.sh
