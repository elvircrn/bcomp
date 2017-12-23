#!/bin/bash
cp app/src/methods.inc lib/src/
echo "Generating parser and scanner for b.atg"
cococpp app/src/b.atg -frames /usr/share/coco-cpp/ -o lib/src
echo "Building compiler"
g++ app/src/main.cpp lib/src/Scanner.cpp lib/src/Parser.cpp -o build/b -std=c++17

