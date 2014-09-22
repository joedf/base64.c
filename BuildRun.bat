@echo off
mkdir bin 2>NUL
cls
echo compiling...
gcc test.c base64.c -o bin\test.exe
echo running...
bin\test.exe