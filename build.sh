#!/bin/bash

echo "Backuping previous parser and scanner versions" 
cp lib/src/Parser.cpp lib/backup/ParserCopy.cpp
cp lib/src/Scanner.cpp lib/backup/ScannerCopy.cpp
cp lib/include/Parser.h lib/backup/ParserCopy.h
cp lib/include/Scanner.h lib/backup/ScannerCopy.h

echo "Removing previous Scanner and Parser versions" 
rm -f lib/src/Parser.cpp lib/src/Scanner.cpp lib/src/include/Parser.h lib/src/include/Scanner.h

echo "Generating parser and scanner for b.atg"
cococpp lib/src/b.atg -frames /usr/share/coco-cpp/ -o lib/src
mv lib/src/Parser.h lib/include/
mv lib/src/Scanner.h lib/include/

