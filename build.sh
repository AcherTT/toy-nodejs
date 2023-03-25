#!/bin/sh

if [ -d "./build" ]; then
    cd build
else
    mkdir build
    cd build
fi

cmake .. && make && cp ../toy-node.js .
