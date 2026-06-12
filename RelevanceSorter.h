#pragma once // header guard

#include <queue> // priority_queue ke liye
#include <vector> // vector ke liye
#include "Document.h" // Document type

// RelevanceSorter uses a max-heap (priority_queue) to order documents by relevanceScore.
class RelevanceSorter {
private:
    struct Compare {
        bool operator()(const Document &a, const Document &b) const {
            return a.relevanceScore < b.relevanceScore; // jiska score zyada, woh upar aaye (max-heap)
        }
    };
    std::priority_queue<Document, std::vector<Document>, Compare> pq; // Heap to store documents by score
public:
    void addDocument(const Document &doc); // Document add karo ranking ke liye
    std::vector<Document> getRankedResults(); // Ranked list return karega
    void displayRanked(); // Console pe ranked results print karega
};
