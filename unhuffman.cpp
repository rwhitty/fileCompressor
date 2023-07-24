#include<iostream>
#include<sstream>
#include<vector>
#include "unhuffman.h"

using namespace std;

Unhuffman::Unhuffman(string bits, string decoder) {
    this->bits = bits;
    this->decoder = decoder;
}

unordered_map<string, char> Unhuffman::decompress_map() {
    vector<string> decode_lines;
    istringstream dec_stream(this->decoder);
    string line;

    while (getline(dec_stream, line)) {
        decode_lines.push_back(line);
    }
    
    unordered_map<string, char> final_map;


    for (const auto& line: decode_lines) {
        int i = 0;
        string key;

        while (line[i] == '0' || line[i] == '1') {
            key += line[i];
            i += 1;
        }

        i += 2;

        final_map[key] = line[i];
    }

    return final_map;
}