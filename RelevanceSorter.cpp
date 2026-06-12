#include "RelevanceSorter.h"
#include <iostream> // cout ke liye

void RelevanceSorter::addDocument(const Document &doc) {
    pq.push(doc); // Document ko heap mein push karo
}

std::vector<Document> RelevanceSorter::getRankedResults() {
    std::vector<Document> out; // Results store karne ke liye
    auto copy = pq; // Original heap ko change nahi karne ke liye copy banao
    while (!copy.empty()) { // Jab tak copy empty na ho
        out.push_back(copy.top()); // Top (highest relevance) nikal ke list mein add karo
        copy.pop(); // Pop kar do
    }
    return out; // Ranked list return karo
}

void RelevanceSorter::displayRanked() {
    auto results = getRankedResults(); // Ranked results lo
    if (results.empty()) {
        std::cout << "No documents to rank.\n"; // Agar kuch nahi hai toh user ko batao
        return;
    }
    std::cout << "Ranked Documents (highest relevance first):\n"; // Heading
    for (const auto &d : results) {
        std::cout << "ID: " << d.id << " Title: " << d.title << " Score: " << d.relevanceScore << "\n"; // Ek-ek document print karo
    }
}
