#pragma once // header guard

#include <queue> // priority_queue ke liye
#include "Document.h" // Document type
#include <vector> // vector

// SpaceManager suggests compression order using a greedy approach: compress files with max savings first.
class SpaceManager {
private:
    struct Compare {
        bool operator()(const Document &a, const Document &b) const {
            return a.fileSize < b.fileSize; // Jiska size zyada, woh pehle aana chahiye (max-heap)
        }
    };
    std::priority_queue<Document, std::vector<Document>, Compare> pq; // Heap of files by size
public:
    void addFile(const Document &doc); // File add karo
    std::vector<Document> suggestCompressionOrder(); // Compression order suggest karega
    void displaySuggestions(); // Print suggestions
};
