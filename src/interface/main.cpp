#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>
#include "../core/Car.h"
#include "../structures/HashTable.h"
#include "../structures/SkipList.h"
#include "../utils/DataLoader.h"
#include "LookupEngine.h"

// Display menu
void displayMenu() {
    std::cout << "\n=== AutoRank Vehicle Lookup System ===" << std::endl;
    std::cout << "1. Search for a vehicle" << std::endl;
    std::cout << "2. Display data structure statistics" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Enter your choice (1-3): ";
}

// Clear input buffer
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Get valid year
int getValidYear() {
    int year;
    while (true) {
        std::cout << "Enter year (1900-2024): ";
        if (std::cin >> year && year >= 1900 && year <= 2024) {
            return year;
        }
        std::cout << "Invalid year. Please enter a year between 1900 and 2024." << std::endl;
        clearInput();
    }
}

// Trim whitespace from string
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

// Get valid string
std::string getValidString(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin >> std::ws, input);
        input = trim(input); // Trim whitespace
        if (!input.empty()) {
            return input;
        }
        std::cout << "Input cannot be empty. Please try again." << std::endl;
    }
}

// Handle vehicle search with input validation and performance comparison
void searchVehicle(LookupEngine& engine) {
    std::cout << "\n=== Vehicle Search ===" << std::endl;
    
    int year = getValidYear();
    std::string make = getValidString("Enter make: ");
    std::string model = getValidString("Enter model: ");
    
    // Perform lookup in both data structures and compare performance
    LookupResult result = engine.performLookup(year, make, model);
    
    engine.displayResults(result);
    engine.displayPerformanceComparison(result);
}

// Display internal statistics for both data structures
void displayStatistics(HashTable& hashTable, SkipList& skipList) {
    std::cout << "\n=== Data Structure Statistics ===" << std::endl;
    std::cout << "Hash Table:" << std::endl;
    std::cout << "  - Size: " << hashTable.getSize() << " entries" << std::endl;
    std::cout << "  - Capacity: " << hashTable.getCapacity() << " slots" << std::endl;
    std::cout << "  - Load Factor: " << std::fixed << std::setprecision(3) << hashTable.getLoadFactor() << std::endl;
    
    std::cout << "\nSkip List:" << std::endl;
    std::cout << "  - Size: " << skipList.getSize() << " entries" << std::endl;
    std::cout << "  - Max Level: " << skipList.getMaxLevel() << std::endl;
    std::cout << "  - Current Level: " << skipList.getCurrentLevel() << std::endl;
    std::cout << "==============================\n" << std::endl;
}

int main() {
    std::cout << "Initializing AutoRank Vehicle Lookup System..." << std::endl;
    
    // Initialize data structures
    HashTable hashTable;
    SkipList skipList;
    
    // Load data from CSV file
    DataLoader loader;
    if (!loader.loadData()) {
        std::cout << "Failed to load data. Exiting." << std::endl;
        return 1;
    }
    
    // Populate data structures
    loader.populateDataStructures(hashTable, skipList);
    
    // Initialize lookup engine
    LookupEngine engine(hashTable, skipList);
    
    std::cout << "\nSystem ready! You can now search for vehicles." << std::endl;
    
    // Main program loop
    int choice;
    while (true) {
        displayMenu();
        
        if (std::cin >> choice) {
            switch (choice) {
                case 1:
                    searchVehicle(engine);
                    break;
                case 2:
                    displayStatistics(hashTable, skipList);
                    break;
                case 3:
                    std::cout << "Thank you for using AutoRank!" << std::endl;
                    return 0;
                default:
                    std::cout << "Invalid choice. Please enter 1, 2, or 3." << std::endl;
            }
        } else {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            clearInput();
        }
    }
    
    return 0;
} 