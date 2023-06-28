#include <iostream>
#include <string>

using namespace std;

class Huffman {
    public:
        unordered_map<char, int> char_counts;
        Huffman(string& file_contents) {
            for (char& c: file_contents) {
                if (char_counts.count(c)) {
                    char_counts[c] += 1;
                } else {
                    char_counts[c] = 1;
                }
            }
        }

    private:    
        class Node {
            public:
                char val;
                double weight;
                Node* zero;
                Node* one;
                Node(char val, double weight, Node* left, Node* right) {
                    this->val = val;
                    this->weight = weight;
                    this->zero = left;
                    this->one = right;
                }
        };

        Node generate_huffman_tree() {
            vector<Node> sorted_chars;
            for (const auto& entry: char_counts) {
                sorted_chars.push_back(Node(entry.first, entry.second, nullptr, nullptr));
            }
            sort(sorted_chars.begin(), sorted_chars.end(), [&](Node n1, Node n2) {
                return char_counts[n1.val] < char_counts[n2.val];
            });
            Node* curr_smallest = nullptr;
        }
};