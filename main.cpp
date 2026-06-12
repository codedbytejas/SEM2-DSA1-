#include <iostream> // cout, cin ke liye
#include <string> // string type
#include <unordered_map> // in-memory store ke liye map
#include <limits> // input ignore karne ke liye
#include <algorithm> // reverse wagairah ke liye
#include "Document.h" // Document class
#include "ConfigManager.h" // Config manager
#include "IndexQueue.h" // Indexing queue
#include "Trie.h" // Trie for prefix search
#include "FileIntegrity.h" // Hash based integrity
#include "RelevanceSorter.h" // Priority queue ranking
#include "KnowledgeGraph.h" // Graph for citations
#include "SpaceManager.h" // Space manager

using namespace std; // Simple usage, names directly use karne ke liye

// Simple in-memory store of documents
static unordered_map<int, Document> store; // id -> Document map
static int nextId = 1; // Next document id

Document::Document() : id(0), title(""), path(""), content(""), signature(""), relevanceScore(0), fileSize(0) {} // Default constructor

Document::Document(int id, const string &title, const string &path, const string &content, int relevanceScore, int fileSize)
    : id(id), title(title), path(path), content(content), relevanceScore(relevanceScore), fileSize(fileSize) {} // Parameterized constructor

void Document::generateSignature() {
    std::hash<string> hasher; // Hasher object
    signature = to_string(hasher(title + "|" + path + "|" + content)); // Simple fingerprint from title|path|content
}

int main() {
    ios::sync_with_stdio(false); // Fast IO setting
    cin.tie(nullptr); // cin/cout ka flush control

    ConfigManager config; // Configuration manager object
    IndexQueue indexQueue; // Indexing queue object
    Trie trie; // Trie for path prefix search
    FileIntegrity integrity; // For duplicate checks
    RelevanceSorter sorter; // For ranking docs
    KnowledgeGraph graph; // For citations
    SpaceManager space; // For compression suggestions

    while (true) {
        cout << "========= DocPulse =========\n\n"; // Menu header
        cout << "1. Add Document\n"; // Option 1
        cout << "2. Search File Path Prefix\n"; // Option 2
        cout << "3. Change Search Configuration\n"; // Option 3
        cout << "4. Undo Configuration\n"; // Option 4
        cout << "5. Upload Document for Indexing\n"; // Option 5
        cout << "6. Process Next Document\n"; // Option 6
        cout << "7. Verify Duplicate Document\n"; // Option 7
        cout << "8. Rank Documents by Relevance\n"; // Option 8
        cout << "9. Add Citation Between Documents\n"; // Option 9
        cout << "10. Display Knowledge Graph\n"; // Option 10
        cout << "11. Find Shortest Citation Path\n"; // Option 11
        cout << "12. Suggest File Compression Order\n"; // Option 12
        cout << "13. Exit\n"; // Option 13
        cout << "Enter choice: "; // Prompt
        int choice; if (!(cin >> choice)) return 0; // Agar input fail ho toh exit karo
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Input buffer clear

        if (choice == 1) {
            string title, path, content; // Local variables to read doc data
            int relevance, size;
            cout << "Title: "; getline(cin, title); // Read title line
            cout << "Path: "; getline(cin, path); // Read path line
            cout << "Content: "; getline(cin, content); // Read content
            cout << "Relevance Score (int): "; cin >> relevance; // Read relevance
            cout << "File size KB (int): "; cin >> size; cin.ignore(); // Read size and clear newline
            Document doc(nextId, title, path, content, relevance, size); // Create document object
            doc.generateSignature(); // Signature generate karo
            store[nextId] = doc; // Store in map
            trie.insert(path, nextId); // Insert path in trie
            sorter.addDocument(doc); // Add to relevance sorter
            space.addFile(doc); // Add to space manager
            cout << "Document added with ID " << nextId << "\n"; // Feedback
            nextId++; // Increment ID for next document
        } else if (choice == 2) {
            string prefix; cout << "Enter prefix: "; getline(cin, prefix); // Read prefix
            auto ids = trie.searchPrefix(prefix); // Search in trie
            trie.displayResults(ids); // Show raw ids
            for (int id : ids) {
                if (store.find(id) != store.end()) {
                    cout << "ID:" << id << " Title:" << store[id].title << " Path:" << store[id].path << "\n"; // Show details
                }
            }
        } else if (choice == 3) {
            string cfg; cout << "Enter new configuration string: "; getline(cin, cfg); // Read new config
            config.changeConfig(cfg); // Apply new config
            cout << "Configuration changed. Current: " << config.getCurrentConfig() << "\n"; // Show current
        } else if (choice == 4) {
            config.undo(); // Undo last change
            cout << "After undo, current configuration: " << config.getCurrentConfig() << "\n"; // Show current
        } else if (choice == 5) {
            int id; cout << "Enter document ID to upload for indexing: "; cin >> id; cin.ignore(); // Read id
            if (store.find(id) == store.end()) cout << "Document not found.\n"; // If not found
            else indexQueue.enqueue(store[id]); // Else enqueue document
        } else if (choice == 6) {
            Document d; // Temp doc to receive from queue
            if (indexQueue.dequeue(d)) {
                cout << "Processing document ID " << d.id << " for indexing...\n"; // Processing message
                // simulate indexing by adding signature to integrity store
                size_t sig = integrity.generateSignature(d); // Generate signature
                integrity.storeSignature(sig); // Store signature (simulate indexing)
                cout << "Indexed and signature stored.\n"; // Done message
            } else cout << "No documents to process.\n"; // If queue empty
        } else if (choice == 7) {
            int id; cout << "Enter document ID to verify duplicate: "; cin >> id; cin.ignore(); // Read id
            if (store.find(id) == store.end()) { cout << "Document not found.\n"; continue; } // Check exists
            if (integrity.isDuplicate(store[id])) cout << "Document appears to be a duplicate.\n"; // Duplicate?
            else cout << "Document is unique (or not indexed yet).\n"; // Not duplicate
        } else if (choice == 8) {
            sorter.displayRanked(); // Show ranked documents
        } else if (choice == 9) {
            int a,b; cout << "From Document ID: "; cin >> a; cout << "To Document ID: "; cin >> b; cin.ignore(); // Read edge
            graph.addCitation(a,b); // Add citation edge
            cout << "Citation added.\n"; // Feedback
        } else if (choice == 10) {
            graph.displayGraph(); // Show graph
        } else if (choice == 11) {
            int a,b; cout << "Source ID: "; cin >> a; cout << "Destination ID: "; cin >> b; cin.ignore(); // Read source and dest
            auto path = graph.findShortestPath(a,b); // BFS path
            if (path.empty()) cout << "No path found.\n"; // If empty
            else {
                cout << "Shortest path: ";
                for (int id : path) cout << id << " "; cout << "\n"; // Print path
            }
        } else if (choice == 12) {
            space.displaySuggestions(); // Suggest compression order
        } else if (choice == 13) {
            cout << "Exiting...\n"; break; // Exit loop
        } else {
            cout << "Invalid choice.\n"; // Wrong input
        }

        cout << "\nPress Enter to continue..."; // Pause prompt
        cin.get(); // Wait enter
    }

    return 0; // Program end
}
