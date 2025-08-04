#include "Car.h"
#include <iostream>
#include <iomanip>

void Car::display() const {
    std::cout << "\n=== Vehicle Information ===" << std::endl;
    std::cout << "Year: " << year << std::endl;
    std::cout << "Make: " << make << std::endl;
    std::cout << "Model: " << model << std::endl;
    std::cout << "Trim: " << trim << std::endl;
    std::cout << "Unique ID: " << uniqueId << std::endl;
    std::cout << "Horsepower: " << horsepower << " hp" << std::endl;
    std::cout << "Torque: " << torque << " lb-ft" << std::endl;
    std::cout << "City MPG: " << cityMPG << std::endl;
    std::cout << "Highway MPG: " << highwayMPG << std::endl;
    std::cout << "Driveline: " << driveline << std::endl;
    std::cout << "Transmission: " << transmission << std::endl;
    std::cout << "Hybrid: " << (hybrid ? "Yes" : "No") << std::endl;
    std::cout << "Fuel Type: " << fuelType << std::endl;
    std::cout << "==========================\n" << std::endl;
} 