#ifndef LOOKUPENGINE_H
#define LOOKUPENGINE_H

#include "../core/Car.h"
#include "../structures/HashTable.h"
#include "../structures/SkipList.h"
#include "../utils/Timer.h"
#include <string>

// Stores results from comparing hash table vs skip list performance
struct LookupResult {
    Car* car;              // Pointer to found car (if any)
    double hashTableTime;   // Time taken by hash table lookup (microseconds)
    double skipListTime;    // Time taken by skip list lookup (microseconds)
    bool found;             // Whether the car was found in either structure
    std::string key;        // The search key used
    
    LookupResult() : car(nullptr), hashTableTime(0), skipListTime(0), found(false) {}
};

class LookupEngine {
private:
    HashTable& hashTable;
    SkipList& skipList;
    Timer timer;
    
public:
    // Constructor initializes with references to both data structures
    LookupEngine(HashTable& ht, SkipList& sl);
    
    // Performs lookup in both structures and times the operations with median averaging
    LookupResult performLookup(int year, const std::string& make, const std::string& model);
    
    // Displays car information if found, or not found message
    void displayResults(const LookupResult& result);
    
    // Shows performance comparison between hash table and skip list
    void displayPerformanceComparison(const LookupResult& result);
    
    // Creates composite key from year, make, and model for consistent lookups
    static std::string generateKey(int year, const std::string& make, const std::string& model);
};

#endif 