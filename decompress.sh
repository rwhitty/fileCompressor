#!/usr/bin/env bash

echo What is the full path of the directory containing file you want to decompress?

read dir_path

echo What is the full path of the location where you want the decompressed file?

read location

raw_bits=$(find "$dir_path" -type f -name "*.bin")
decoder=$(find "$dir_path" -type f -name "*.txt")

set +x

g++ -std=c++11 decode.cpp unhuffman.cpp

(echo "$decoder"; echo "$raw_bits"; echo "$location") | ./a.out > /dev/null