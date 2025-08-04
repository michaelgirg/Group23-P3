#ifndef CAR_H
#define CAR_H

#include <string>

struct Car {
    std::string id;
    int year;
    std::string make;
    std::string model;
    std::string trim;
    std::string uniqueId;
    int horsepower;
    int torque;
    int cityMPG;
    int highwayMPG;
    std::string driveline;
    std::string transmission;
    bool hybrid;
    std::string fuelType;
    
    // Default constructor initializes all fields to safe values
    Car() : year(0), horsepower(0), torque(0), cityMPG(0), highwayMPG(0), hybrid(false) {}
    
    // Full constructor creates car with all specified parameters
    Car(const std::string& id, int year, const std::string& make, const std::string& model,
        const std::string& trim, const std::string& uniqueId, int horsepower, int torque, 
        int cityMPG, int highwayMPG, const std::string& driveline, const std::string& transmission, 
        bool hybrid, const std::string& fuelType)
        : id(id), year(year), make(make), model(model), trim(trim), uniqueId(uniqueId),
          horsepower(horsepower), torque(torque), cityMPG(cityMPG), highwayMPG(highwayMPG), 
          driveline(driveline), transmission(transmission), hybrid(hybrid), fuelType(fuelType) {}
    
    // Creates composite key for hash table and skip list lookups
    std::string getCompositeKey() const {
        return std::to_string(year) + make + model;
    }
    
    // Displays formatted car information to console
    void display() const;
};

#endif 