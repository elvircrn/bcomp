#!/bin/bash
echo "Generating parser and scanner for b.atg"
cococpp b.atg -frames /usr/share/coco-cpp/
echo "Building compiler"
g++ main.cpp Scanner.cpp Parser.cpp -o b -std=c++17

