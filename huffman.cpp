#include <iostream>
#include <string>
#include <queue>

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
                bool operator<(const Node& other) {
                    return this->weight < other.weight;
                }
                bool operator>(const Node& other) {
                    return this->weight > other.weight;
                }
        };

        Node generate_huffman_tree() {
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
                Node smallest2 = nodes_queue.top();
                nodes_queue.pop();
                Node lowest_combined = Node(
                    char(0), smallest1.weight + smallest2.weight, &smallest2, &smallest1
                );
                nodes_queue.push(lowest_combined);
            }
            return nodes_queue.top();
        }
};