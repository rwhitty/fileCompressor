#ifndef UNHUFFMAN_H
#define UNHUFFMAN_H

#include <string>

using namespace std;

class Unhuffman {
    public:
        Unhuffman(string bits, string decoder);
        string final_text();
        string bits;
        string decoder;

    private:
        unordered_map<string, char> decompress_map();
};

#endif