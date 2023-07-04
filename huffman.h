#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>

using namespace std;

class Huffman {
    public:
        unordered_map<char, int> char_counts;
        string file_contents;
        Huffman(string& file_contents);
        string final_bitstring();
    private:
        class Node {
            public:
                char val;
                double weight;
                Node* zero;
                Node* one;
                Node(char val, double weight, Node* left, Node* right);
                bool operator<(const Node& other) const;
                bool operator>(const Node& other) const;
        };
        Node generate_huffman_tree();
        unordered_map<char, string> generate_huffman_map(Node& huffman_tree);
        void dfs_explore(Node start, string bits, unordered_map<char, string>& huffman_map);
};

#endif