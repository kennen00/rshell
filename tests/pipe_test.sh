#!/bin/sh

./start.sh

echo Hello > temp/test1
echo 12345 > temp/test3

../bin/rshell < inputs/pipe_input.txt > pipe_output.txt
echo -e "\n" >> pipe_output.txt

if cmp -s pipe_output.txt expects/pipe_expect.txt; then 
    echo Tests Passed!

else 
    echo Tests Failed!
    diff pipe_output.txt expects/pipe_expect.txt
fi

./clean.sh
