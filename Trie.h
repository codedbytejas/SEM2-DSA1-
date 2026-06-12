#pragma once // header guard

#include <vector>  // vector use karne ke liye
#include <string>  // string ke liye
#include <memory>  // smart pointers ke liye
#include "Document.h" // Document type
using std::string; // short name

// Trie Node for file path and name indexing. Each node stores children for characters.
struct TrieNode {
    bool isEnd; // Kya yeh node kisi path ka akhir hai? (end marker)
    std::vector<std::shared_ptr<TrieNode>> children; // Har character ka child (128 ASCII)
    std::vector<int> docIds; // Agar yeh end hai toh yahan document IDs store hongi
    TrieNode(); // Constructor
};

class Trie {
private:
    std::shared_ptr<TrieNode> root; // Root node jahan se search/insert start hota hai
    void collectAll(std::shared_ptr<TrieNode> node, const string &prefix, std::vector<int> &out); // Helper to gather results
public:
    Trie(); // Constructor jo root banayega
    void insert(const string &path, int docId); // Path insert karne ke liye
    std::vector<int> searchPrefix(const string &prefix); // Prefix se matching doc IDs dhoondo
    void displayResults(const std::vector<int> &docIds); // Results print karne ke liye
};
