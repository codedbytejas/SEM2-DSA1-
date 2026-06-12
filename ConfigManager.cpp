#include "ConfigManager.h"
#include <iostream> // cout ke liye

ConfigManager::ConfigManager(): currentConfig("default") {} // Default config "default" set kar diya

void ConfigManager::changeConfig(const string &newConfig) {
    // Push current to history and update
    history.push(currentConfig); // Current setting ko history mein save kar do (undo ke liye)
    currentConfig = newConfig;   // Nayi configuration apply kar do
}

void ConfigManager::undo() {
    if (history.empty()) { // Agar history khali hai toh undo possible nahi
        std::cout << "No previous configuration to undo.\n"; // User ko bata do
        return; // Function yahin stop
    }
    currentConfig = history.top(); // Stack ka top last saved config hai, use wapas current bana do
    history.pop(); // Usko stack se hata do kyunki ab restore ho chuka
}

string ConfigManager::getCurrentConfig() const {
    return currentConfig; // Abhi ka active configuration return karo
}

void ConfigManager::displayHistory() const {
    // Can't inspect stack directly without copying; skip heavy debug.
    std::cout << "Configuration history size: " << history.size() << "\n"; // History mein kitne entries hain print karo
}
