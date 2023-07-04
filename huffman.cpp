#include <iostream>
#include <string>
#include <queue>
#include "huffman.h"

using namespace std;

Huffman::Huffman(string& file_contents) {
    this->file_contents = file_contents;
    for (char& c: file_contents) {
        if (char_counts.count(c)) {
            char_counts[c] += 1;
        } else {
            char_counts[c] = 1;
        }
    }
}

string Huffman::final_bitstring() {
    Node huffman_tree = generate_huffman_tree();
    unordered_map<char, string> huffman_map = generate_huffman_map(huffman_tree);
    string return_string;
    for (char& c: file_contents) {
        return_string += huffman_map[c];
    }
    return return_string;
}

Huffman::Node::Node(char val, int weight, Node* left, Node* right) {
    this->val = val;
    this->weight = weight;
    this->zero = left;
    this->one = right;
}

bool Huffman::Node::operator<(const Node& other) const {
    return this->weight < other.weight;
}

bool Huffman::Node::operator>(const Node& other) const {
    return this->weight > other.weight;
}

Huffman::Node Huffman::generate_huffman_tree() {
    priority_queue<Node, vector<Node>, greater<Node>> nodes_queue;
    for (const auto& entry: char_counts) {
        Node curr_node = Node(entry.first, entry.second, nullptr, nullptr);
        nodes_queue.push(curr_node);
    }
    Node lowest_weight = nodes_queue.top();
    nodes_queue.pop();
    while (nodes_queue.size() > 1) {
        Node smallest1 = nodes_queue.top();
        nodes_queue.pop();
        cout << "test1: " << smallest1.val << smallest1.weight << "\n";
        Node smallest2 = nodes_queue.top();
        nodes_queue.pop();
        cout << "test2: " << smallest2.val << smallest2.weight << "\n";
        Node lowest_combined = Node(
            char(0), smallest1.weight + smallest2.weight, &smallest2, &smallest1
        );
        nodes_queue.push(lowest_combined);
    }
    return nodes_queue.top();
}

unordered_map<char, string> Huffman::generate_huffman_map(Node& huffman_tree) {
    unordered_map<char, string> huffman_map;
    dfs_explore(huffman_tree, "", huffman_map);
    return huffman_map;
}

void Huffman::dfs_explore(Node start, string bits, unordered_map<char, string>& huffman_map) {
    if (start.zero == nullptr || start.one == nullptr) {
        huffman_map[start.val] = bits;
    } else {
        dfs_explore(*start.zero, bits + "0", huffman_map);
        dfs_explore(*start.one, bits + "1", huffman_map);
    }
}
