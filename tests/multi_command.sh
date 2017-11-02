#!/bin/sh

echo hello; ls -a -l; ps
echo hello again && ls -al && mk && echo no run
mkdir src || echo hello once again || ls -a
echo goodbye; ls -a && pwd || git status
