#!/bin/bash

git pull origin master
cmake -H. -BBuild -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -Wdev
cd Build
make -j 2
app/BompilerApp
