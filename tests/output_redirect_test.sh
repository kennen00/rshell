#!/bin/sh

./start.sh

echo hello > temp/test1
echo 12345 > temp/test3

../bin/rshell < inputs/output_redirect_input.txt > output_redirect_output.txt
echo -e "\n" >> output_redirect_output.txt

if cmp -s output_redirect_output.txt expects/output_redirect_expect.txt; then 
    echo Tests Passed!

else 
    echo Tests Failed!
    diff output_redirect_output.txt expects/output_redirect_expect.txt
fi

./clean.sh
