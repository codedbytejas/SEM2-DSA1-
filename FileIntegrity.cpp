#include "FileIntegrity.h"
#include <functional> // std::hash use karne ke liye

size_t FileIntegrity::generateSignature(const Document &doc) {
    std::hash<string> hasher; // Hasher object
    // Combine several fields for better uniqueness
    string combined = doc.title + "|" + doc.path + "|" + doc.content; // Title|path|content se ek string bana lo
    return hasher(combined); // Hash return karo (fingerprint)
}

bool FileIntegrity::isDuplicate(const Document &doc) {
    size_t sig = generateSignature(doc); // Pehle signature nikal lo
    return signatures.find(sig) != signatures.end(); // Set mein hai kya check karo
}

void FileIntegrity::storeSignature(size_t sig) {
    signatures.insert(sig); // Signature ko set mein add kar do
}
