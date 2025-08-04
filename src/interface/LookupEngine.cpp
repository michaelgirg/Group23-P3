#include "LookupEngine.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

LookupEngine::LookupEngine(HashTable& ht, SkipList& sl) : hashTable(ht), skipList(sl) {}

LookupResult LookupEngine::performLookup(int year, const std::string& make, const std::string& model) {
    LookupResult result;
    result.key = generateKey(year, make, model);
    
    // Time hash table lookup with multiple iterations and median calculation
    const int iterations = 50;
    std::vector<double> hashTimes;
    
    for (int run = 0; run < 5; run++) {
        timer.reset();
        timer.start();
        for (int i = 0; i < iterations; i++) {
            result.car = hashTable.find(result.key);
        }
        timer.stop();
        hashTimes.push_back(timer.getElapsedTime() / iterations);
    }
    
    // Calculate median of hash table times
    std::sort(hashTimes.begin(), hashTimes.end());
    result.hashTableTime = hashTimes[hashTimes.size() / 2];
    
    // Time skip list lookup with multiple iterations and median calculation
    std::vector<double> skipTimes;
    Car* skipListCar = nullptr;
    
    for (int run = 0; run < 5; run++) {
        timer.reset();
        timer.start();
        for (int i = 0; i < iterations; i++) {
            skipListCar = skipList.find(result.key);
        }
        timer.stop();
        skipTimes.push_back(timer.getElapsedTime() / iterations);
    }
    
    // Calculate median of skip list times
    std::sort(skipTimes.begin(), skipTimes.end());
    result.skipListTime = skipTimes[skipTimes.size() / 2];
    
    // Set result based on whether car was found
    if (result.car || skipListCar) {
        result.found = true;
        if (!result.car) result.car = skipListCar;
    }
    
    return result;
}

void LookupEngine::displayResults(const LookupResult& result) {
    if (result.found && result.car) {
        result.car->display();
    } else {
        // Show search details when vehicle not found
        std::cout << "\nVehicle not found in database." << std::endl;
        std::cout << "Searched for: " << result.key << std::endl;
    }
}

void LookupEngine::displayPerformanceComparison(const LookupResult& result) {
    std::cout << "\n=== Performance Comparison ===" << std::endl;
    std::cout << "Search Key: " << result.key << std::endl;
    std::cout << "Hash Table Time: " << Timer::formatTime(result.hashTableTime) << std::endl;
    std::cout << "Skip List Time: " << Timer::formatTime(result.skipListTime) << std::endl;
    
    // Calculate and display performance ratio (skip list time / hash table time)
    if (result.hashTableTime > 0 && result.skipListTime > 0) {
        double ratio = result.skipListTime / result.hashTableTime;
        std::cout << "Skip List is " << std::fixed << std::setprecision(2) << ratio << "x ";
        
        if (ratio > 1) {
            std::cout << "slower than Hash Table" << std::endl;
        } else {
            std::cout << "faster than Hash Table" << std::endl;
        }
    }
    
    std::cout << "=============================\n" << std::endl;
}

std::string LookupEngine::generateKey(int year, const std::string& make, const std::string& model) {
    // Concatenate year, make, and model to create unique lookup key
    return std::to_string(year) + make + model;
} 