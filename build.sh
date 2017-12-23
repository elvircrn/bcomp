#!/bin/bash
echo "Removing previous Scanner and Parser versions"
rm -f lib/src/Parser.cpp lib/src/Scanner.cpp lib/src/include/Parser.h lib/src/include/Scanner.h
echo "Generating parser and scanner for b.atg"
cococpp lib/src/b.atg -frames /usr/share/coco-cpp/ -o lib/src
mv lib/src/Parser.h lib/include/
mv lib/src/Scanner.h lib/include/

