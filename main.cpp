#include<iostream>
#include<fstream>
#include<string>
#include "huffman.h"

using namespace std;

void write_to_file(const string& bits, const string& filename);

int main() {
    string filepath;
    cout << "Please type the absolute path of your file: ";
    cin >> filepath;
    ifstream file(filepath);
    if (!file.good()) {
        throw invalid_argument("Nonexistent filepath.");
    }
    string text_contents = "";
    string line;
    while (getline(file, line)) {
        text_contents += line;
    }
    Huffman file_huffman = Huffman(text_contents);
    string bitstring = file_huffman.final_bitstring();
    string compressed_filepath;
    cout << "Please type the desired path of the compressed file: ";
    cin >> compressed_filepath;
    write_to_file(bitstring, compressed_filepath);
    return 0;
}

void write_to_file(const string& bits, const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file.good()) {
        throw invalid_argument("Invalid filepath.");
    }
    size_t num_bytes = bits.length() / 8;
    if (bits.length() % 8 != 0) {
        num_bytes++;
    }
    string bytes;
    for (size_t i = 0; i < num_bytes; i++) {
        string curr_byte = bits.substr(i * 8, 8);
        unsigned char byte = 0;
        for (size_t pos = 0; pos < curr_byte.length(); pos++) {
            byte <<= 1;
            if (curr_byte[pos] == '1') {
                byte |= 1;
            }
        }
        bytes.push_back(byte);
    }
    file.write(bytes.data(), bytes.size());
    file.close();
}