#include "SpaceManager.h"
#include <iostream> // cout ke liye

void SpaceManager::addFile(const Document &doc) {
    pq.push(doc); // File ko heap mein add kar do
}

std::vector<Document> SpaceManager::suggestCompressionOrder() {
    std::vector<Document> out; // Result list
    auto copy = pq; // Original heap ko change nahi karne ke liye copy banao
    while (!copy.empty()) {
        out.push_back(copy.top()); // Largest file pehle add karo
        copy.pop();
    }
    return out; // Return ordered list
}

void SpaceManager::displaySuggestions() {
    auto results = suggestCompressionOrder(); // Suggestions lo
    if (results.empty()) {
        std::cout << "No files to suggest for compression.\n"; // Agar kuch nahi hai toh bata do
        return;
    }
    std::cout << "Suggested compression order (largest savings first):\n"; // Heading
    for (const auto &d : results) {
        std::cout << "ID: " << d.id << " Title: " << d.title << " Size(KB): " << d.fileSize << "\n"; // Print each suggestion
    }
}
