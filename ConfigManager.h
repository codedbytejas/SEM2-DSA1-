#pragma once // header ko ek hi baar include karna

#include <string> // string type ke liye
#include <stack>  // stack container use karne ke liye
using std::string; // simple naam ke liye

// ConfigManager uses a stack to allow undo of configuration changes.
// LIFO behavior ensures the most recent change is undone first.
class ConfigManager {
private:
    std::stack<string> history; // Purani configurations ko store karta hai (plates jaise - last in first out)
    string currentConfig;       // Abhi jo configuration active hai wo yahan store hoti hai
public:
    ConfigManager(); // Constructor jo default config set karega
    void changeConfig(const string &newConfig); // Nayi configuration apply karne ke liye
    void undo(); // Last change ko wapas lene ke liye (undo)
    string getCurrentConfig() const; // Abhi ka config return karega
    void displayHistory() const; // Debug/inspect ke liye history size dikhata hai
};
