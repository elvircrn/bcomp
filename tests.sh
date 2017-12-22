#!/bin/bash
cococpp b.atg -frames /usr/share/coco-cpp/
g++ test.cpp Scanner.cpp Parser.cpp -o b


