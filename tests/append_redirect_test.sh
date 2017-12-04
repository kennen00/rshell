#!/bin/sh

./start.sh

echo hello > temp/test1
echo 12345 > temp/test3

../bin/rshell < inputs/append_redirect_input.txt > append_redirect_output.txt
echo -e "\n" >> append_redirect_output.txt

if cmp -s append_redirect_output.txt expects/append_redirect_expect.txt; then 
    echo Tests Passed!

else 
    echo Tests Failed!
    diff append_redirect_output.txt expects/append_redirect_expect.txt
fi

./clean.sh
