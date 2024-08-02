# File Compressor Project

Welcome! This tool, which I built in summer 2023, uses provably-optimal Huffman Encoding to losslessly compress text files. It achieves an average compression ratio of roughly 2:1, and
can compress hundreds of megabytes worth of text in a manner of seconds.

## Usage

To use the tool, first clone this repository and `cd` into the root directory of the project. 

To compress files, run the compression shell script with `bash compress.sh`, which will prompt you for filepaths of the file you are compressing and the directory you want the compressed file to
be placed in. Assuming valid filepaths, this will generate a new directory that contains the compressed text file (as a binary file) and a small text file used to decompress that file
later on.

To decompress files, run the decompression shell script with `bash decompress.sh`, which will also prompt you for filepaths of the directory containing the compressed binary file and the 
filepath you want the decompressed text file to be placed in, including the actual `.txt` filename. Assuming valid filepaths, this will generate a text file with the provided filename/path
that contains exactly the same information as the original, compressed file.

## Technical Overview

The tool is written entirely in C++. It works by scanning the entire text file, counting each character and storing each unique character in a "node" of the Huffman tree, which also contains 
its frequency. This scanning is multithreaded, which achieves a several-fold speedup (the exact number depends on the number of threads available in the hardware, to which it is flexible). 
Then, a greedy algorithm isused which continually "merges" the two nodes with the lowest frequencies (tracked using a heap) until all nodes are connected in a tree structure. The structure of 
this tree determinesthe prefix-free binary encoding mapped to each character. For more details on the nature of this data structure, see [here](https://en.wikipedia.org/wiki/Huffman_coding).

The file is then scanned again, this time writing each character's corresponding binary encoding to a new binary file. Lastly, the mapping of binary encodings to characters
is stored in a very small text file in the same parent directory as the aforementioned binary file. This text file is used to decode the binary file back into text, which is possible
losslessly due to the prefix-free nature of the Huffman codes.
