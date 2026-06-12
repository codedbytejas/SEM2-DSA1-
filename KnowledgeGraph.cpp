#include "KnowledgeGraph.h"
#include <iostream> // cout ke liye
#include <queue> // BFS ke liye queue
#include <unordered_map> // parent map ke liye
#include <limits>

void KnowledgeGraph::addCitation(int fromId, int toId) {
    adj[fromId].push_back(toId); // fromId se toId ki taraf edge add karo
}

void KnowledgeGraph::displayGraph() const {
    std::cout << "Knowledge Graph:\n"; // Heading
    for (const auto &p : adj) {
        std::cout << p.first << " -> "; // Node jis se edges jaate hain
        for (int to : p.second) std::cout << to << " "; // Sab outgoing nodes print karo
        std::cout << "\n";
    }
}

std::vector<int> KnowledgeGraph::neighbors(int id) const {
    auto it = adj.find(id); // Check karo kya id graph mein hai
    if (it == adj.end()) return {}; // Agar nahi toh empty vector return karo
    return it->second; // Nahi toh neighbors return karo
}

std::vector<int> KnowledgeGraph::findShortestPath(int src, int dst) const {
    // BFS to find shortest path in unweighted directed graph
    std::unordered_map<int, int> parent; // Har node ka parent store karne ke liye
    std::queue<int> q; // BFS queue
    q.push(src); // Start se push karo
    parent[src] = -1; // Source ka parent -1 mark karo
    while (!q.empty()) {
        int u = q.front(); q.pop(); // Current node
        if (u == dst) break; // Agar destination mil gaya toh break
        auto it = adj.find(u);
        if (it == adj.end()) continue; // Agar koi outgoing edges nahi hain toh continue
        for (int v : it->second) {
            if (parent.find(v) == parent.end()) { // Agar v visit nahi hua
                parent[v] = u; // Parent set karo
                q.push(v); // Queue mein add karo
            }
        }
    }
    if (parent.find(dst) == parent.end()) return {}; // Agar dst tak parent assign nahi hua matlab path nahi mila
    std::vector<int> path;
    for (int cur = dst; cur != -1; cur = parent[cur]) path.push_back(cur); // Parent chain se path nikaalo
    std::reverse(path.begin(), path.end()); // Reverse karke source se destination order banalo
    return path; // Return path
}
