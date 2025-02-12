#include "Map.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>

Map::Map() {
    // Initialize all distances to a value representing no direct connection
    for (int i = 0; i < MAX_SIZE; ++i) {
        for (int j = 0; j < MAX_SIZE; ++j) {
            distanceMatrix[i][j] = std::numeric_limits<int>::max(); // No connection initially
        }
    }
    // Initialize all provinces as unvisited
    resetVisited();
}

// Loads distance data from a file and fills the distanceMatrix
void Map::loadDistanceData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    int row = 0;

    while (std::getline(file, line) && row < MAX_SIZE) {
        std::stringstream ss(line);
        std::string value;
        int col = 0;

        while (std::getline(ss, value, ',') && col < MAX_SIZE) {
            distanceMatrix[row][col] = std::stoi(value); // Convert string to integer and populate matrix
            ++col;
        }
        ++row;
    }

    file.close();
}

// Checks if the distance between two provinces is within the allowed maxDistance
bool Map::isWithinRange(int provinceA, int provinceB, int maxDistance) const {
    std::cout << "Checking distance from " << provinceA << " to " << provinceB << ": " 
              << distanceMatrix[provinceA][provinceB] << std::endl;
    return distanceMatrix[provinceA][provinceB] <= maxDistance;
}


// Marks a province as visited
void Map::markAsVisited(int province) {
    visited[province] = true;
}

// Checks if a province has already been visited
bool Map::isVisited(int province) const {
    return visited[province];
}

// Resets all provinces to unvisited
void Map::resetVisited() {
    for (int i = 0; i < MAX_SIZE; ++i) {
        visited[i] = false;
    }
}

// Function to count the number of visited provinces
int Map::countVisitedProvinces() const {
    int count = 0;
    for (int i = 0; i < MAX_SIZE; ++i) {
        if (visited[i]) {
            ++count;
        }
    }
    return count;
}

// Function to get the distance between two provinces
int Map::getDistance(int provinceA, int provinceB) const {
    return distanceMatrix[provinceA][provinceB];
}