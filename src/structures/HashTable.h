#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../core/Car.h"
#include <string>
#include <vector>

class HashTable {
private:
    // Represents a single entry in the hash table
    struct HashEntry {
        std::string key;
        Car car;
        bool isOccupied;  // True if this slot contains data
        bool isDeleted;    // True if this slot was deleted (for lazy deletion)
        
        HashEntry() : isOccupied(false), isDeleted(false) {}
    };
    
    std::vector<HashEntry> table;  // The actual hash table storage
    size_t size;                   // Number of elements currently stored
    size_t capacity;               // Total number of slots available
    static const size_t DEFAULT_CAPACITY = 100000;
    
    // Converts string key to table index using hash function
    size_t hash(const std::string& key) const;
    // Handles collisions by finding next available slot
    size_t probe(const std::string& key, size_t index) const;
    // Resizes table when load factor gets too high for performance
    void resize();
    
public:
    // Constructor initializes hash table with specified capacity
    HashTable(size_t initialCapacity = DEFAULT_CAPACITY);
    
    // Inserts car into table, updates if key exists, resizes if load factor > 70%
    void insert(const std::string& key, const Car& car);
    
    // Searches for car by key, returns pointer if found, nullptr otherwise
    Car* find(const std::string& key);
    
    // Removes car using lazy deletion (marks as deleted but keeps data)
    void remove(const std::string& key);
    
    // Returns current number of elements stored in table
    size_t getSize() const { return size; }
    
    // Returns total capacity of hash table for load factor calculation
    size_t getCapacity() const { return capacity; }
    
    // Returns load factor as ratio of size to capacity
    double getLoadFactor() const { return static_cast<double>(size) / capacity; }
};

#endif 