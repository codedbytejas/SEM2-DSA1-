#pragma once // Header ko ek hi baar include karne ke liye (avoid duplicate include)

#include <string> // string type use karne ke liye
using std::string; // string ko simple naam se use karne ke liye

// Document class represents a single document in DocPulse
// Ye class document ki saari basic information rakhta hai
class Document {
public:
    int id;                    // Document ka unique number (jaise roll number)
    string title;              // Document ka naam ya title
    string path;               // File system path, jaise /eng/spec.txt
    string content;            // Document ka content (simplified)
    string signature;          // Chhota fingerprint for duplicate check
    int relevanceScore;        // Search ranking score (bada matlab zyada relevant)
    int fileSize; // in KB for simplicity // File size KB mein

    Document(); // Default constructor // object banaane ka default tareeka
    Document(int id, const string &title, const string &path, const string &content, int relevanceScore, int fileSize); // Parameterized constructor

    // Generate signature using std::hash<string>
    void generateSignature(); // Signature banana ka function
};
