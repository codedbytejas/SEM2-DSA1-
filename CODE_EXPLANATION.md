CODE_EXPLANATION for DocPulse

This document explains every source and header file in the DocPulse project in plain, layman-friendly language. It walks through key lines and blocks so a non-expert (or a beginner) can understand what each file does and why it matters.

---

1) Document.h
----------------
- Purpose: defines the Document "record" used throughout the program. Think of Document as a folder card that tracks everything about a file.

Contents explained:
- `#pragma once` : Stops this file from being accidentally included more than once.
- `#include <string>` and `using std::string;` : Lets the code use the string type to store text.
- The `Document` class lists properties:
  - `int id;` : a unique number to identify the document.
  - `string title;` : human-readable title.
  - `string path;` : file path like `/eng/specA.txt`.
  - `string content;` : the actual text (simplified for this project).
  - `string signature;` : a short, fixed-size string generated from title+path+content to check uniqueness.
  - `int relevanceScore;` : a score used to rank how relevant a document is for search results.
  - `int fileSize;` : approximate file size in KB; used by SpaceManager.
- The constructors and `generateSignature()` are declared here; their implementation lives in `main.cpp` so the class has simple methods to create instances and signatures.

Why it matters: `Document` holds all metadata in one object so every module (indexer, trie, graph, etc.) can share information easily.

---

2) ConfigManager.h / ConfigManager.cpp
-----------------------------------------
- Purpose: stores and manages search engine settings. Allows "undo" so the latest change can be rolled back.

Key ideas in `ConfigManager.h`:
- It keeps a `std::stack<string>` named `history` which stores old settings.
- `currentConfig` is the currently active configuration string.
- Public methods: `changeConfig()`, `undo()`, `getCurrentConfig()`.

What the `.cpp` does (behavior explained):
- Constructor sets `currentConfig` to "default".
- `changeConfig(newConfig)`:
  - pushes the current setting onto the stack so it can be restored later.
  - updates `currentConfig` to the new value.
- `undo()`:
  - If the stack is empty, nothing to undo.
  - Otherwise, pop the top of stack and set it as `currentConfig`.
- `getCurrentConfig()` returns the currently active configuration.

Layman explanation: think of the stack as an "undo stack" in a text editor: every time you change a setting, we remember the previous one so you can go back.

---

3) IndexQueue.h / IndexQueue.cpp
----------------------------------
- Purpose: model a pipeline where uploaded documents are queued for indexing in the order they arrive (first-in-first-out).

Key parts:
- `std::queue<Document> q;` holds documents.
- `enqueue(doc)` pushes a document to the back.
- `dequeue(outDoc)` removes the front document and returns it by reference. Returns false if the queue is empty.
- `displayPending()` prints how many are pending.

Layman: It's like a line at a bank teller — the first customer in line is served first.

---

4) Trie.h / Trie.cpp
----------------------
- Purpose: store file paths so we can quickly find all documents starting with a path prefix (like "/eng" -> all engineering docs).

Structure explained:
- `struct TrieNode` holds:
  - `isEnd` which marks if a node corresponds to the end of a stored path.
  - `children` which is a vector of 128 pointers — one for each ASCII character; each pointer leads to the next character node.
  - `docIds` stores document ids that end at this node.
- `Trie` has a `root` node and provides `insert(path, docId)` and `searchPrefix(prefix)`.

How insertion works (in plain words):
- Start at the root node.
- For every character in the path string, go to the child node for that character; if it doesn't exist, create it.
- At the end, mark the node as an end and store the document id there.

How searchPrefix works:
- Walk down the nodes following the prefix characters.
- If at any point a required child does not exist, no documents match the prefix.
- Otherwise, once you reach the node for the prefix, collect all document IDs in that node and every child node below it (this is done with `collectAll`).

Why Trie is used: Tries give extremely fast prefix queries — the time is proportional to the length of the search prefix, not proportional to the number of stored paths.

---

5) FileIntegrity.h / FileIntegrity.cpp
----------------------------------------
- Purpose: create a small "signature" for each document and use a hash-set to detect duplicates quickly.

Key parts:
- `generateSignature(doc)` uses `std::hash<string>` on a combined string of title|path|content — this produces a number that acts as a signature.
- `isDuplicate(doc)` checks if this signature is already in the stored set.
- `storeSignature(sig)` inserts a signature into the set.

Plain language: We create a short fingerprint for each file; if two files have the same fingerprint they are probably duplicates. This is similar to how deduplication works in many storage systems (though production systems use strong cryptographic hashes for safety).

---

6) RelevanceSorter.h / RelevanceSorter.cpp
--------------------------------------------
- Purpose: rank documents by their relevance score so we can show the most relevant first.

Main idea:
- Uses `std::priority_queue` with a custom comparator that sorts by `relevanceScore` descending.
- `addDocument` pushes into the heap.
- `getRankedResults` copies the heap and pops elements to produce a list ordered from highest relevance to lowest.
- `displayRanked` prints these out.

Layman: Priority queue acts like a judge that always points to the most important item; if you ask repeatedly you'll get the top ones first.

---

7) KnowledgeGraph.h / KnowledgeGraph.cpp
-----------------------------------------
- Purpose: model citations or links between documents as a graph so we can answer questions like "how is doc A related to doc B?"

Structure:
- `adj` is an `unordered_map<int, vector<int>>` mapping a document ID to the list of documents it cites (directed edges).
- `addCitation(from, to)` adds a directed edge.
- `displayGraph()` prints each node and its outgoing edges.
- `neighbors(id)` returns documents directly linked from `id`.
- `findShortestPath(src, dst)` uses BFS to find the shortest number of steps from src to dst.

BFS explained:
- Start from src and explore nodes level-by-level.
- Keep track of each visited node's parent so once dst is found we can reconstruct the route by following parents back to src.
- If dst is not visited, no path exists.

Layman: The graph is a map of who cites whom. BFS finds the fewest "citation hops" between two documents.

---

8) SpaceManager.h / SpaceManager.cpp
-------------------------------------
- Purpose: suggest which files to compress first using a greedy idea: compress files that save the most space first.

Approach:
- Uses a max-heap (`priority_queue`) ordered by `fileSize` (a proxy for compression savings).
- `addFile(doc)` pushes into heap.
- `suggestCompressionOrder()` pops all elements from a copy of the heap to return files from largest to smallest.

Layman: If you want to free up space fast, zip the biggest files first — this is the heuristic used here.

---

9) main.cpp
------------
- Purpose: provides a menu-driven user interface that connects all modules.

Key parts and flow:
- Global in-memory `store` (unordered_map<int, Document>) stores added documents by id. `nextId` is used to generate unique ids.
- The `Document` constructor and the `generateSignature()` method are implemented at the top of `main.cpp` for convenience.
- The program constructs one instance of each module (ConfigManager, IndexQueue, Trie, FileIntegrity, RelevanceSorter, KnowledgeGraph, SpaceManager).
- The program then enters a loop showing the menu and reading a numeric choice.

Menu options and what each does:
1. Add Document
- Prompts for title, path, content, relevance, size.
- Generates ID and signature, stores in `store`, inserts into `trie`, adds to `sorter` and `space` manager.

2. Search File Path Prefix
- Prompts for prefix string.
- Uses trie to find document IDs matching prefix and prints their metadata.

3. Change Search Configuration
- Reads a new configuration string and calls `config.changeConfig()`.

4. Undo Configuration
- Calls `config.undo()` to revert to previous configuration (demonstrates stack LIFO).

5. Upload Document for Indexing
- Prompts for document ID and pushes it to `indexQueue`.

6. Process Next Document
- Pops next doc from `indexQueue` and stores its signature in `FileIntegrity` to simulate indexing.

7. Verify Duplicate Document
- Checks if a document's signature is found in the `FileIntegrity` set.

8. Rank Documents by Relevance
- Shows documents from highest to lowest relevance using `RelevanceSorter`.

9. Add Citation Between Documents
- Adds a directed edge in the knowledge graph.

10. Display Knowledge Graph
- Prints adjacency lists showing citations.

11. Find Shortest Citation Path
- Runs BFS to find and print the shortest path between two doc IDs.

12. Suggest File Compression Order
- Uses `SpaceManager` to show files sorted by fileSize (largest first).

13. Exit
- Quits program.

Why `main.cpp` matters: it demonstrates how these data structures can work together to form a small search-engine-like system.

---

Notes for students / instructors
- The project uses simple in-memory structures for clarity. In real systems you'd add persistence, stronger hashing (e.g., SHA), and efficient disk-backed indices.
- Each module shows one or two DSA concepts and standard library containers.
- Complexity information is given in README.md and comments in the source files.

---

If you'd like, I can also:
- Expand this file to include a line-by-line walkthrough of any single source file (e.g., `Trie.cpp`) with commented excerpts.
- Produce a short narrated walkthrough (script) you can read during a viva.

End of CODE_EXPLANATION.md
