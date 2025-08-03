#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

class TrieNode {
public:
    // Map from character to child node
    std::unordered_map<char, TrieNode*> children;
    
    // Flag to mark end of a word
    bool isEndOfWord;
    
    TrieNode() : isEndOfWord(false) {}
    
    ~TrieNode() {
        // Clean up all child nodes
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};

class Trie {
private:
    TrieNode* root;
    
public:
    Trie() {
        root = new TrieNode();
    }
    
    ~Trie() {
        delete root;
    }
    
    // Insert a word into the trie
    void insert(const std::string& word) {
        TrieNode* current = root;
        
        // Traverse/create path for each character
        for (char ch : word) {
            // If child doesn't exist, create it
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        
        // Mark the end of word
        current->isEndOfWord = true;
    }
    
    // Search for a word in the trie
    bool search(const std::string& word) {
        TrieNode* current = root;
        
        // Follow the path character by character
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return false; // Path doesn't exist
            }
            current = current->children[ch];
        }
        
        // Word exists only if we reach a node marked as end of word
        return current->isEndOfWord;
    }
    
    // Check if there's any word starting with given prefix
    bool startsWith(const std::string& prefix) {
        TrieNode* current = root;
        
        // Just need to follow the path - don't care about isEndOfWord
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        
        return true; // Prefix path exists
    }
    
    // Helper function to print all words with given prefix
    void printWordsWithPrefix(const std::string& prefix) {
        TrieNode* current = root;
        
        // Navigate to the prefix
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                std::cout << "No words found with prefix: " << prefix << std::endl;
                return;
            }
            current = current->children[ch];
        }
        
        // DFS to find all words from this point
        std::vector<std::string> results;
        dfsCollectWords(current, prefix, results);
        
        std::cout << "Words with prefix '" << prefix << "':" << std::endl;
        for (const std::string& word : results) {
            std::cout << "  " << word << std::endl;
        }
    }
    
private:
    void dfsCollectWords(TrieNode* node, const std::string& currentWord, 
                        std::vector<std::string>& results) {
        if (node->isEndOfWord) {
            results.push_back(currentWord);
        }
        
        for (auto& pair : node->children) {
            char ch = pair.first;
            TrieNode* child = pair.second;
            dfsCollectWords(child, currentWord + ch, results);
        }
    }
};

// Demo usage
int main() {
    Trie trie;
    
    // Insert some words
    std::vector<std::string> words = {"cat", "car", "card", "care", "careful", "cats", "dog"};
    
    std::cout << "Inserting words: ";
    for (const std::string& word : words) {
        std::cout << word << " ";
        trie.insert(word);
    }
    std::cout << std::endl << std::endl;
    
    // Test search
    std::vector<std::string> searchWords = {"car", "card", "cards", "care", "careful"};
    for (const std::string& word : searchWords) {
        std::cout << "Search '" << word << "': " 
                  << (trie.search(word) ? "Found" : "Not found") << std::endl;
    }
    std::cout << std::endl;
    
    // Test prefix search
    std::vector<std::string> prefixes = {"car", "cat", "do", "xyz"};
    for (const std::string& prefix : prefixes) {
        std::cout << "Prefix '" << prefix << "' exists: " 
                  << (trie.startsWith(prefix) ? "Yes" : "No") << std::endl;
    }
    std::cout << std::endl;
    
    // Print all words with prefix
    trie.printWordsWithPrefix("car");
    std::cout << std::endl;
    trie.printWordsWithPrefix("cat");
    
    return 0;
}