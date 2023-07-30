#include<iostream>
#include<fstream>
#include<string>
#include "huffman.h"

using namespace std;

void write_bits(const string& bits, const string& filename);

void write_decoder(const unordered_map<char, string>& decoder, const string& file_prefix);

int main() {

    string filepath;

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

    file.close();

    Huffman file_huffman = Huffman(text_contents);
    string bitstring = file_huffman.final_bitstring();
    string compressed_filepath;

    cin >> compressed_filepath;

    string new_name = filepath.substr(
        filepath.find_last_of("/"),
        filepath.find_last_of(".") - filepath.find_last_of("/")
    );

    write_bits(bitstring, compressed_filepath + new_name);

    unordered_map<char, string> decoder = file_huffman.decoder;
    write_decoder(decoder, compressed_filepath + new_name);

    return 0;
}

void write_bits(const string& bits, const string& filename) {

    ofstream file(filename + "_compressed.bin", ios::binary);

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

void write_decoder(const unordered_map<char, string>& decoder, const string& file_prefix) {

    string decode_string = "";

    for (const auto& encoding: decoder) {
        decode_string += encoding.second + ": " + encoding.first + "\n";
    }

    ofstream decode_file(file_prefix + "_decoder.txt");
    decode_file << decode_string;
    decode_file.close();
}