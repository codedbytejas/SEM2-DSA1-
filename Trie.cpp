#include "Trie.h"
#include <iostream> // cout ke liye

TrieNode::TrieNode(): isEnd(false), children(128, nullptr) {} // Node banao, saare children initially null

Trie::Trie(): root(std::make_shared<TrieNode>()) {} // Root node create karo

void Trie::insert(const string &path, int docId) {
    // Complexity: O(L) where L = length of path
    auto node = root; // Start root se
    for (char ch : path) { // Har character ke liye
        unsigned char idx = static_cast<unsigned char>(ch); // Character ka index lo (0-127)
        if (!node->children[idx]) node->children[idx] = std::make_shared<TrieNode>(); // Agar child nahi hai toh naya banao
        node = node->children[idx]; // Aage badho
    }
    node->isEnd = true; // Path ka end mark kar do
    node->docIds.push_back(docId); // Is path se associated document id add karo
}

std::vector<int> Trie::searchPrefix(const string &prefix) {
    // Complexity: O(P + R) where P=prefix length, R=results collected
    auto node = root; // Start root se
    for (char ch : prefix) { // Prefix ke characters follow karo
        unsigned char idx = static_cast<unsigned char>(ch);
        if (!node->children[idx]) return {}; // Agar path break ho jaye toh empty return
        node = node->children[idx]; // Aage badho
    }
    std::vector<int> out; // Results collect karne ke liye
    collectAll(node, prefix, out); // Sab child nodes se ids collect karo
    return out; // Return list of doc ids
}

void Trie::collectAll(std::shared_ptr<TrieNode> node, const string &prefix, std::vector<int> &out) {
    if (!node) return; // Safety check
    if (node->isEnd) {
        for (int id : node->docIds) out.push_back(id); // Agar yeh end hai toh IDs add karo
    }
    for (int i = 0; i < 128; ++i) { // Har possible child check karo
        if (node->children[i]) {
            collectAll(node->children[i], prefix + static_cast<char>(i), out); // Recursively collect
        }
    }
}

void Trie::displayResults(const std::vector<int> &docIds) {
    if (docIds.empty()) {
        std::cout << "No results found.\n"; // Agar kuch nahi mila
        return;
    }
    std::cout << "Found document IDs: "; // IDs print karo
    for (int id : docIds) std::cout << id << " "; // Ek-ek ID print karte jao
    std::cout << "\n";
}
