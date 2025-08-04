#include "SkipList.h"
#include <iostream>
#include <algorithm>

SkipList::SkipList(int maxLvl) : maxLevel(maxLvl), currentLevel(1), size(0), gen(rd()), dis(0, 1) {
    header = new SkipNode("", Car(), maxLevel);
}

SkipList::~SkipList() {
    SkipNode* current = header;
    while (current != nullptr) {
        SkipNode* next = current->forward[0];
        delete current;
        current = next;
    }
}

int SkipList::randomLevel() {
    int level = 1;
    while (dis(gen) == 1 && level < maxLevel) {
        level++;
    }
    return level;
}

SkipList::SkipNode* SkipList::createNode(const std::string& key, const Car& car, int level) {
    return new SkipNode(key, car, level);
}

void SkipList::insert(const std::string& key, const Car& car) {
    std::vector<SkipNode*> update(maxLevel, nullptr);
    SkipNode* current = header;
    
    // Search from top level down to find insertion position
    for (int i = currentLevel - 1; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;  // Remember nodes that will need pointer updates
    }
    
    current = current->forward[0];
    
    // If key already exists, update the car
    if (current != nullptr && current->key == key) {
        current->car = car;
        return;
    }
    
    // Create new node with random level (coin flip simulation)
    int newLevel = randomLevel();
    if (newLevel > currentLevel) {
        for (int i = currentLevel; i < newLevel; i++) {
            update[i] = header;  // Header will point to new node at higher levels
        }
        currentLevel = newLevel;
    }
    
    SkipNode* newNode = createNode(key, car, newLevel);
    
    // Update forward pointers at each level
    for (int i = 0; i < newLevel; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
    
    size++;
}

Car* SkipList::find(const std::string& key) {
    SkipNode* current = header;
    
    // Search from top level down to skip large distances at high levels
    for (int i = currentLevel - 1; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }
    
    // Check the next node at level 0 (bottom level)
    current = current->forward[0];
    
    if (current != nullptr && current->key == key) {
        return &current->car;
    }
    
    return nullptr;
}

void SkipList::remove(const std::string& key) {
    std::vector<SkipNode*> update(maxLevel, nullptr);
    SkipNode* current = header;
    
    // Find the node to remove
    for (int i = currentLevel - 1; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    
    if (current != nullptr && current->key == key) {
        // Update forward pointers
        for (int i = 0; i < currentLevel; i++) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }
        
        // Update current level if needed
        while (currentLevel > 1 && header->forward[currentLevel - 1] == nullptr) {
            currentLevel--;
        }
        
        delete current;
        size--;
    }
} 