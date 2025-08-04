#ifndef DATALOADER_H
#define DATALOADER_H

#include "../core/Car.h"
#include "../structures/HashTable.h"
#include "../structures/SkipList.h"
#include <string>
#include <vector>
#include <fstream>

class DataLoader {
private:
    std::string filename;  // CSV file to load data from
    std::vector<Car> cars; // Temporary storage for parsed cars
    
    // Parses single CSV line into Car object with proper field mapping
    Car parseCarFromLine(const std::string& line);
    // Splits string by delimiter for CSV parsing
    std::vector<std::string> split(const std::string& str, char delimiter);
    // Converts string to boolean for hybrid field
    bool parseBoolean(const std::string& str);
    
public:
    // Constructor sets filename for CSV data loading with default dataset
    DataLoader(const std::string& fname = "unique_cars_dataset.csv");
    
    // Loads and parses CSV file into cars vector with error handling
    bool loadData();
    
    // Inserts all cars into both data structures using composite keys
    void populateDataStructures(HashTable& hashTable, SkipList& skipList);
    
    // Returns reference to loaded cars vector for external access
    const std::vector<Car>& getCars() const { return cars; }
    
    // Returns number of cars loaded from CSV for statistics
    size_t getCarCount() const { return cars.size(); }
};

#endif 