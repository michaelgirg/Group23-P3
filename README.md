# AutoRank - Vehicle Lookup System

A C++ application that compares the performance of Hash Table vs Skip List data structures for vehicle information retrieval.

## Project Overview

AutoRank allows users to search for vehicle specifications by Year, Make, and Model. The system performs lookups using both a custom Hash Table and Skip List implementation, providing performance comparisons between the two data structures.

## Features

- **Vehicle Search**: Look up cars by Year, Make, and Model
- **Performance Comparison**: Compare lookup times between Hash Table and Skip List
- **Data Structure Statistics**: View size, capacity, and load factor information
- **Robust Input Handling**: Trims whitespace and validates user input
- **Consistent Timing**: Median-based timing measurements for reliable results
- **Real Dataset**: Uses comprehensive vehicle database with 6,150+ cars

## Data Structure Implementations

### Hash Table
- Open addressing with linear probing
- Dynamic resizing when load factor exceeds 0.7
- Composite key: "Year+Make+Model"
- O(1) average case lookup time

### Skip List
- Multi-level linked list structure
- Random level generation for optimal performance
- Maintains sorted order by composite key
- O(log n) average case lookup time

## Getting Started

### Prerequisites
- C++11 compatible compiler (GCC 4.8+ or Clang 3.3+)
- Make utility

### Building the Project
```bash
# Build the project
make

# Build with debug information
make debug

# Build with optimization
make release

# Clean build files
make clean

# Build and run
make run
```

### Running the Application
```bash
./autorank
```

## Usage

### Main Menu Options
1. **Search for a vehicle** - Look up car specifications
2. **Display data structure statistics** - View performance metrics
3. **Exit** - Close the application

### Vehicle Search
- Enter Year (1900-2024)
- Enter Make (e.g., Honda, Toyota, Tesla)
- Enter Model (e.g., Accord, Camry, Model S)
- View detailed vehicle information and performance comparison

### Results Display
- Complete vehicle specifications (Year, Make, Model, Trim, Unique ID, etc.)
- Performance comparison between Hash Table and Skip List
- Timing information in microseconds with consistent measurements

## Data Format

The system uses a comprehensive vehicle dataset with the following CSV format:
```
ID,Year,Make,Model,Trim,Unique_ID,Horsepower,Torque,City MPG,Highway MPG,Driveline,Transmission,Hybrid,Fuel Type
```

The dataset includes over 6,150 vehicles with detailed specifications.

## Performance Metrics

The system measures and compares:
- **Lookup Time**: Microsecond precision timing with median averaging
- **Memory Usage**: Structure size and capacity information
- **Load Factor**: Hash table efficiency metrics
- **Consistent Results**: Multiple timing runs for reliable measurements

## Technical Details

- **Language**: C++11
- **Data Structures**: Custom Hash Table and Skip List
- **Timing**: High-resolution chrono library with median averaging
- **Input Validation**: Robust error handling with whitespace trimming
- **Memory Management**: RAII principles
- **Build System**: Clean Makefile with organized build directory

## Example Output

```
=== Vehicle Information ===
Year: 2022
Make: Honda
Model: Accord
Trim: Convenience
Unique ID: Honda_Accord_2022_Convenience
Horsepower: 149 hp
Torque: 226 lb-ft
City MPG: 25
Highway MPG: 38
Driveline: FWD
Transmission: CVT
Hybrid: No
Fuel Type: Gasoline
==========================

=== Performance Comparison ===
Search Key: 2022HondaAccord
Hash Table Time: 0.06 μs
Skip List Time: 0.08 μs
Skip List is 1.33x slower than Hash Table
=============================
```

## Team Members

- **Michael Girgis**: Hash Table implementation
- **Lathan Price**: Skip List implementation  
- **Nelson Lu**: CLI interface and user input parsing

## Project Structure

```
Group23-P3/
├── src/
│   ├── core/           # Car data structure
│   ├── structures/     # HashTable and SkipList implementations
│   ├── utils/          # DataLoader and Timer utilities
│   └── interface/      # LookupEngine and main application
├── unique_cars_dataset.csv  # Vehicle database
├── Makefile           # Build configuration
├── .gitignore         # Git ignore rules
└── README.md          # This file
```

