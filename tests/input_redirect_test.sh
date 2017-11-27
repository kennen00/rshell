#!/bin/sh

./start.sh

echo hello > temp/test1
echo 12345 > temp/test3

../bin/rshell < inputs/input_redirect_input.txt > input_redirect_output.txt
echo -e "\n" >> input_redirect_output.txt

if cmp -s input_redirect_output.txt expects/input_redirect_expect.txt; then 
    echo Tests Passed!

else 
    echo Tests Failed!
    diff input_redirect_output.txt expects/input_redirect_expect.txt
fi

./clean.sh
