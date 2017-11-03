#!/bin/sh
#This test is different from the others, as it doesn't use text files
#If this test runs all the way through with no instances of rshell remaining, then it has succeeded
echo exit | ../bin/rshell
echo "ls -a; exit && /ps" | ../bin/rshell
echo "ls -al; pwd && exit" | ../bin/rshell
