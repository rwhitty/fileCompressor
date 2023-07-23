#!/usr/bin/env bash

echo What is the name of the file you want to compress?

read filepath

echo What is the location where you want the compressed file?

read location

g++ -std=c++11 encode.cpp huffman.cpp

(echo "$filepath"; echo "$location") | ./a.out > /dev/null