#!/usr/bin/env bash

echo What is the name of the file you want to compress?

read filepath

echo What is the location where you want the compressed file?

read location

echo $filepath

echo $location

g++ -std=c++11 main.cpp huffman.cpp

echo -e "$filepath\n$location" | ./a.out > /dev/null