#!/bin/sh

echo exit | ../bin/rshell
echo "ls -a; exit && /ps" | ../bin/rshell
echo "ls -al; pwd && exit" | ../bin/rshell
