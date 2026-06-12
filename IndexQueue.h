#pragma once // header ko ek baar include karne ke liye

#include <queue> // FIFO queue ke liye
#include "Document.h" // Document type ke liye
using std::queue; // simple naam

// IndexQueue processes documents in FIFO order to simulate indexing pipeline
class IndexQueue {
private:
    queue<Document> q; // Documents ka line/queue (pehle aaya pehle process)
public:
    void enqueue(const Document &doc); // Naya document queue mein daalo
    bool dequeue(Document &outDoc); // Next document nikaalo, false agar empty ho
    void displayPending() const; // Kitne pending documents hain dikhata hai
    bool isEmpty() const; // Check karo kya queue khali hai
};
