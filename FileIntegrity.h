#pragma once // header guard

#include <string> // string type
#include <unordered_set> // unordered_set for fast lookup
#include "Document.h" // Document type
using std::string;

// FileIntegrity uses hashing to generate signatures and an unordered_set to track uniqueness.
class FileIntegrity {
private:
    std::unordered_set<size_t> signatures; // Signatures ka set, fast lookup ke liye
public:
    size_t generateSignature(const Document &doc); // Signature banata hai
    bool isDuplicate(const Document &doc); // Check karta hai agar duplicate hai
    void storeSignature(size_t sig); // Signature store karta hai
};
