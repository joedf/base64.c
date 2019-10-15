#!/bin/bash
{ set +x; } 2>/dev/null
mkdir bin 2>/dev/null
clear
echo compiling...
gcc test.c base64.c -o bin/test
gcc b64f.c base64.c -s -o bin/b64f
echo running...
bin/test
echo
echo Encoding test image "picture.png" to "picture.b64.txt"...
bin/b64f e picture.png picture.b64.txt
echo
echo Decoding test image from "picture.b64.txt" to "picture.b64.png"...
bin/b64f d picture.b64.txt picture.b64.png
echo Done.
echo Check the files manually to see if the program works correctly.




