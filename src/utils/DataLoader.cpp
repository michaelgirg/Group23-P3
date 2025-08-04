#include "DataLoader.h"
#include <iostream>
#include <sstream>
#include <algorithm>

DataLoader::DataLoader(const std::string& fname) : filename(fname) {}

bool DataLoader::loadData() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open " << filename << ". Please ensure the CSV file exists." << std::endl;
        return false;
    }
    
    std::string line;
    // Skip header line since it contains column names
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            Car car = parseCarFromLine(line);
            cars.push_back(car);
        }
    }
    
    file.close();
    std::cout << "Loaded " << cars.size() << " cars from " << filename << std::endl;
    return true;
}

Car DataLoader::parseCarFromLine(const std::string& line) {
    std::vector<std::string> fields = split(line, ',');
    
    // Ensure we have all 14 required fields for the new dataset format
    if (fields.size() < 14) {
        return Car(); // Return empty car if line is bad
    }
    
    // Map CSV fields to Car object fields based on dataset format:
    // ID,Year,Make,Model,Trim,Unique_ID,Horsepower,Torque,City MPG,Highway MPG,Driveline,Transmission,Hybrid,Fuel Type
    return Car(
        fields[0], // id
        std::stoi(fields[1]), // year
        fields[2], // make
        fields[3], // model
        fields[4], // trim
        fields[5], // uniqueId
        std::stoi(fields[6]), // horsepower
        std::stoi(fields[7]), // torque
        std::stoi(fields[8]), // cityMPG
        std::stoi(fields[9]), // highwayMPG
        fields[10], // driveline
        fields[11], // transmission
        parseBoolean(fields[12]), // hybrid
        fields[13] // fuelType
    );
}

std::vector<std::string> DataLoader::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    // Split string by delimiter and store in vector
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

bool DataLoader::parseBoolean(const std::string& str) {
    std::string upper = str;
    // Convert to uppercase for case-insensitive comparison
    std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    return upper == "TRUE" || upper == "1" || upper == "YES";
}

void DataLoader::populateDataStructures(HashTable& hashTable, SkipList& skipList) {
    for (const Car& car : cars) {
        // Use composite key (year + make + model) for consistent lookups
        std::string key = car.getCompositeKey();
        hashTable.insert(key, car);
        skipList.insert(key, car);
    }
    
    std::cout << "Populated data structures with " << cars.size() << " cars" << std::endl;
    std::cout << "Hash Table - Size: " << hashTable.getSize() 
              << ", Load Factor: " << hashTable.getLoadFactor() << std::endl;
    std::cout << "Skip List - Size: " << skipList.getSize() 
              << ", Max Level: " << skipList.getMaxLevel() << std::endl;
}

