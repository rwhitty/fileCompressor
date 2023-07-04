#include<iostream>
#include<fstream>
#include<string>
#include "huffman.h"

using namespace std;

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
    //string bitstring = file_huffman.final_bitstring();
    //cout << bitstring;
    return 0;
}
