#!/bin/sh

./start.sh

../bin/rshell < inputs/precedence_input.txt > precedence_output.txt
echo -e "\n" >> precedence_output.txt

if cmp -s precedence_output.txt expects/precedence_expect.txt; then
    echo Tests Passed!
else
    echo Tests Failed!
    diff precedence_output.txt expects/precedence_expect.txt
fi

./clean.sh
