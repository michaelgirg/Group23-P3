#include "HashTable.h"
#include <iostream>

HashTable::HashTable(size_t initialCapacity) : size(0), capacity(initialCapacity) {
    table.resize(capacity);
}

size_t HashTable::hash(const std::string& key) const {
    size_t hashValue = 0;
    for (char c : key) {
        // Multiply by prime and add character value for better distribution and collision resolution
        hashValue = (hashValue * 31 + c) % capacity;
    }
    return hashValue;
}

size_t HashTable::probe(const std::string& key, size_t index) const {
    size_t i = 0;
    while (i < capacity) {
        size_t currentIndex = (index + i) % capacity;
        // Found empty slot or matching key
        if (!table[currentIndex].isOccupied || table[currentIndex].key == key) {
            return currentIndex;
        }
        i++;
    }
    return index; // Should never reach here if table isn't full
}

void HashTable::insert(const std::string& key, const Car& car) {
    // Resize if load factor exceeds 70%
    if (getLoadFactor() > 0.7) {
        resize();
    }
    
    size_t index = hash(key);
    size_t insertIndex = probe(key, index);
    
    if (!table[insertIndex].isOccupied) {
        // Insert new entry
        table[insertIndex].key = key;
        table[insertIndex].car = car;
        table[insertIndex].isOccupied = true;
        table[insertIndex].isDeleted = false;
        size++;
    } else if (table[insertIndex].key == key) {
        // Update existing entry
        table[insertIndex].car = car;
    }
}

Car* HashTable::find(const std::string& key) {
    size_t index = hash(key);
    size_t searchIndex = probe(key, index);
    
    if (table[searchIndex].isOccupied && table[searchIndex].key == key) {
        return &table[searchIndex].car;
    }
    
    return nullptr;
}

void HashTable::remove(const std::string& key) {
    size_t index = hash(key);
    size_t removeIndex = probe(key, index);
    
    // Lazy deletion: mark as deleted but keep data for collision resolution
    if (table[removeIndex].isOccupied && table[removeIndex].key == key) {
        table[removeIndex].isOccupied = false;
        table[removeIndex].isDeleted = true;
        size--;
    }
}

// Double the table size and rehash all existing entries
void HashTable::resize() {
    std::vector<HashEntry> oldTable = table;
    size_t oldCapacity = capacity;
    
    capacity *= 2;
    table.clear();
    table.resize(capacity);
    size = 0;
    
    // Rehash all valid entries from old table
    for (size_t i = 0; i < oldCapacity; i++) {
        if (oldTable[i].isOccupied && !oldTable[i].isDeleted) {
            insert(oldTable[i].key, oldTable[i].car);
        }
    }
} 