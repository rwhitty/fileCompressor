#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<bitset>
#include "unhuffman.h"

using namespace std;

void write_original(const string& contents, const string& filepath);

int main() {

    string decoder_path;

    cin >> decoder_path;

    ifstream decode_file(decoder_path);

    if (!decode_file.good()) {
        throw invalid_argument("Nonexistent filepath.");
    }

    string decoder_contents = "";
    string line;

    while (getline(decode_file, line)) {
        decoder_contents += line;
    }

    decode_file.close();

    string binary_path;

    cin >> binary_path;

    ifstream compressed_file(binary_path, ios::binary);

    if (!compressed_file.good()) {
        throw invalid_argument("Nonexistent filepath.");
    }

    stringstream binary_data;
    char byte;
    
    while (compressed_file.get(byte)) {
        binary_data << bitset<8>(byte);
    }

    compressed_file.close();

    string bitstring = binary_data.str();
    Unhuffman unhuffman = Unhuffman(bitstring, decoder_contents);

    string file_text = unhuffman.final_text();

    string new_name = binary_path.substr(
        binary_path.find_last_of("/"),
        binary_path.length() - binary_path.find_last_of("/") - 15
    );

    string decompressed_path;

    cin >> decompressed_path;

    write_original(file_text, decompressed_path + new_name);
}

void write_original(const string& contents, const string& filepath) {

    ofstream original_file(filepath + ".txt");

    if (!original_file.good()) {
        throw invalid_argument("Invalid filepath.");
    }

    original_file << contents;
    original_file.close();
}