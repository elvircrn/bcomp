#!/bin/bash
cp app/src/methods.inc lib/include/
echo "Generating parser and scanner for b.atg"
cococpp lib/src/b.atg -frames /usr/share/coco-cpp/ -o lib/src
mv lib/src/Parser.h lib/include/
mv lib/src/Scanner.h lib/include/
echo "Building compiler"

