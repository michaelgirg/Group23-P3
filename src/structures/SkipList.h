#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "../core/Car.h"
#include <string>
#include <random>

class SkipList {
private:
    // Each node contains data and an array of forward pointers
    struct SkipNode {
        std::string key;
        Car car;
        std::vector<SkipNode*> forward;  // Array of pointers to next nodes at each level
        
        SkipNode(const std::string& k, const Car& c, int level) 
            : key(k), car(c), forward(level, nullptr) {}
    };
    
    SkipNode* header;  // Dummy head node that points to all levels
    int maxLevel;      // Maximum number of levels allowed
    int currentLevel;  // Current highest level in use
    size_t size;       // Number of elements stored
    
    // Random number generation for level assignment
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
    
    // Generates random level for new nodes using coin flip simulation
    int randomLevel();
    // Creates a new node with specified level and data
    SkipNode* createNode(const std::string& key, const Car& car, int level);
    
public:
    // Constructor creates skip list with specified max level
    SkipList(int maxLvl = 16);
    
    // Destructor frees all allocated nodes to prevent memory leaks
    ~SkipList();
    
    // Inserts car with random level assignment, updates if key exists
    void insert(const std::string& key, const Car& car);
    
    // Searches for car by key using multi-level traversal
    Car* find(const std::string& key);
    
    // Removes car and updates forward pointers at all levels
    void remove(const std::string& key);
    
    // Returns current number of elements stored in skip list
    size_t getSize() const { return size; }
    
    // Returns maximum allowed level for nodes in skip list
    int getMaxLevel() const { return maxLevel; }
    
    // Returns current highest level in use for statistics
    int getCurrentLevel() const { return currentLevel; }
};

#endif 