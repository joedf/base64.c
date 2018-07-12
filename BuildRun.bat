@echo off
mkdir bin 2>NUL
cls
echo compiling...
gcc test.c base64.c -o bin\test.exe
gcc b64f.c base64.c -o bin\b64f.exe
echo running...
bin\test.exe
echo.
echo Encoding test image "picture.png" to "picture.b64.txt"...
bin\b64f.exe e picture.png picture.b64.txt
echo.
echo Decoding test image from "picture.b64.txt" to "picture.b64.png"...
bin\b64f.exe d picture.b64.txt picture.b64.png
echo.
echo Done.
echo See files manually if the programmed works correctly.
pause