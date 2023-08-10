#!/usr/bin/env bash

echo What is the full path of the file you want to compress?

read filepath

echo What is the full path of the location where you want the compressed file?

read location

filename=$(basename "$filepath")
filename="${filename%.*}"

set +x

mkdir "${location}/${filename}_compressed"
dir_path="${location}/${filename}_compressed"

g++ -std=c++11 encode.cpp huffman.cpp

(echo "$filepath"; echo "$dir_path") | ./a.out > /dev/null