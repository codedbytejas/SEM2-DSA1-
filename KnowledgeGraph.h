#pragma once // header guard

#include <unordered_map> // adjacency list map ke liye
#include <vector> // vector ke liye
#include <string> // (optional) strings agar use hon

// KnowledgeGraph represents document relationships using adjacency lists (unordered_map<int, vector<int>>)
class KnowledgeGraph {
private:
    std::unordered_map<int, std::vector<int>> adj; // adj list: docID -> list of docIDs it cites
public:
    void addCitation(int fromId, int toId); // Add directed edge from->to
    void displayGraph() const; // Print graph
    std::vector<int> neighbors(int id) const; // Return neighbors of a node
    // BFS shortest path
    std::vector<int> findShortestPath(int src, int dst) const; // Shortest citation path using BFS
};
