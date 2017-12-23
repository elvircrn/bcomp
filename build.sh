#!/bin/bash
cp app/src/methods.inc lib/include/
echo "Generating parser and scanner for b.atg"
cococpp app/src/b.atg -frames /usr/share/coco-cpp/ -o lib/src
mv lib/src/Parser.h lib/include/
mv lib/src/Scanner.h lib/include/
echo "Building compiler"
g++ app/src/main.cpp lib/src/Scanner.cpp lib/src/Parser.cpp -o build/b -std=c++17

