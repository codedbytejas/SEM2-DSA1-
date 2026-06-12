#include "IndexQueue.h"
#include <iostream> // cout ke liye

void IndexQueue::enqueue(const Document &doc) {
    q.push(doc); // Document ko queue ke end mein daal do (FIFO)
}

bool IndexQueue::dequeue(Document &outDoc) {
    if (q.empty()) return false; // Agar queue khali ho toh false return karo
    outDoc = q.front(); // Front se next document le lo
    q.pop(); // Usko queue se hata do
    return true; // Successful dequeue
}

void IndexQueue::displayPending() const {
    std::cout << "Pending documents in indexing queue: " << q.size() << "\n"; // Pending count batao
}

bool IndexQueue::isEmpty() const { return q.empty(); } // Simple check agar queue khali hai
