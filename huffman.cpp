#include <iostream>
#include <string>
#include <queue>
#include "huffman.h"
#include <thread>

using namespace std;

Huffman::Huffman(string& file_contents) {

    this->file_contents = file_contents;

    int num_threads = thread::hardware_concurrency();

    vector<unordered_map<char, int>> small_counts(num_threads);
    vector<thread> threads;
    
    int chunkSize = file_contents.length() / num_threads;
    int remainder = file_contents.length() % num_threads;
    int start = 0;

    for (int i = 0; i < num_threads; i++) {
        int end = start + chunkSize + (i < remainder ? 1 : 0);
        threads.emplace_back(&Huffman::count_chars, this, start, end, &small_counts[i]);
        start = end;
    }

    for (auto& thread : threads) {
        thread.join();
    }

    for (const auto& local_map : small_counts) {
        for (const auto& entry : local_map) {
            char_counts[entry.first] += entry.second;
        }
    }
}

void Huffman::count_chars(int start, int end, unordered_map<char, int>* local_counts) {
    for (int i = start; i < end; i++) {
        char c = this->file_contents[i];
        (*local_counts)[c] += 1;
    }
}

string Huffman::final_bitstring() {

    Node huffman_tree = generate_huffman_tree();
    this->decoder = generate_huffman_map(huffman_tree);
    string return_string;

    for (int i = 0; i < file_contents.length(); i++) {
        char c = file_contents[i];
        return_string += decoder[c];
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

    while (nodes_queue.size() > 1) {
        Node* smallest1 = new Node(nodes_queue.top());
        nodes_queue.pop();
        Node* smallest2 = new Node(nodes_queue.top());
        nodes_queue.pop();
        Node lowest_combined = Node(
            char(0), smallest1->weight + smallest2->weight, smallest2, smallest1
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
