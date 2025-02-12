#include "RoutePlanner.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

// Array to help you out with name of the cities in order
const std::string cities[81] = { 
    "Adana", "Adiyaman", "Afyon", "Agri", "Amasya", "Ankara", "Antalya", "Artvin", "Aydin", "Balikesir", "Bilecik", 
    "Bingol", "Bitlis", "Bolu", "Burdur", "Bursa", "Canakkale", "Cankiri", "Corum", "Denizli", "Diyarbakir", "Edirne", 
    "Elazig", "Erzincan", "Erzurum", "Eskisehir", "Gaziantep", "Giresun", "Gumushane", "Hakkari", "Hatay", "Isparta", 
    "Mersin", "Istanbul", "Izmir", "Kars", "Kastamonu", "Kayseri", "Kirklareli", "Kirsehir", "Kocaeli", "Konya", "Kutahya", 
    "Malatya", "Manisa", "Kaharamanmaras", "Mardin", "Mugla", "Mus", "Nevsehir", "Nigde", "Ordu", "Rize", "Sakarya", 
    "Samsun", "Siirt", "Sinop", "Sivas", "Tekirdag", "Tokat", "Trabzon", "Tunceli", "Urfa", "Usak", "Van", "Yozgat", 
    "Zonguldak", "Aksaray", "Bayburt", "Karaman", "Kirikkale", "Batman", "Sirnak", "Bartin", "Ardahan", "Igdir", 
    "Yalova", "Karabuk", "Kilis", "Osmaniye", "Duzce" 
};

// Constructor to initialize and load constraints
RoutePlanner::RoutePlanner(const std::string& distance_data, const std::string& priority_data, const std::string& restricted_data, int maxDistance)
    : maxDistance(maxDistance), totalDistanceCovered(0), numPriorityProvinces(0), numWeatherRestrictedProvinces(0) {

    map.loadDistanceData(distance_data);
    map.resetVisited();
    loadPriorityProvinces(priority_data);
    loadWeatherRestrictedProvinces(restricted_data);
}

// Load priority provinces from txt file to an array of indices
void RoutePlanner::loadPriorityProvinces(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open priority provinces file: " + filename);
    }

    int province;
    while (file >> province && numPriorityProvinces < MAX_PRIORITY_PROVINCES) {
        priorityProvinces[numPriorityProvinces++] = province;
    }
    file.close();
}

// Load weather-restricted provinces from txt file to an array of indices
void RoutePlanner::loadWeatherRestrictedProvinces(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open weather-restricted provinces file: " + filename);
    }

    int province;
    while (file >> province && numWeatherRestrictedProvinces < MAX_WEATHER_RESTRICTED_PROVINCES) {
        weatherRestrictedProvinces[numWeatherRestrictedProvinces++] = province;
    }
    file.close();
}

// Checks if a province is a priority province
bool RoutePlanner::isPriorityProvince(int province) const {
    return std::find(priorityProvinces, priorityProvinces + numPriorityProvinces, province) != priorityProvinces + numPriorityProvinces;
}

// Checks if a province is weather-restricted
bool RoutePlanner::isWeatherRestricted(int province) const {
    return std::find(weatherRestrictedProvinces, weatherRestrictedProvinces + numWeatherRestrictedProvinces, province) != weatherRestrictedProvinces + numWeatherRestrictedProvinces;
}

// Begins the route exploration from the starting point
void RoutePlanner::exploreRoute(int startingCity) {
    stack.push(startingCity);
    map.markAsVisited(startingCity);
    route.push_back(startingCity);

    while (!stack.isEmpty()) {
        int currentProvince = stack.peek();
        std::cout << "Exploring province: " << cities[currentProvince] << std::endl;

        if (queue.isEmpty()) {
            std::cout << "No neighbors left to explore. Backtracking..." << std::endl;
            backtrack();
        } else {
            int nextProvince = queue.dequeue();
            std::cout << "Dequeued: " << cities[nextProvince] << std::endl;
            stack.push(nextProvince);
            map.markAsVisited(nextProvince);
            route.push_back(nextProvince);
            totalDistanceCovered += map.getDistance(currentProvince, nextProvince);
        }
    }
    std::cout << "Exploration complete." << std::endl;
}




// Helper function to explore from a specific province
void RoutePlanner::exploreFromProvince(int province) {
    enqueueNeighbors(province);

    if (!queue.isEmpty()) {
        int nextProvince = queue.dequeue();
        stack.push(nextProvince);
        map.markAsVisited(nextProvince);
        route.push_back(nextProvince);
        totalDistanceCovered += map.getDistance(province, nextProvince);
    }
}

// Enqueue neighbors based on constraints
void RoutePlanner::enqueueNeighbors(int province) {
    std::cout << "Enqueuing neighbors for: " << cities[province] << std::endl;

    for (int i = 0; i < MAX_SIZE; ++i) {
        if (!map.isVisited(i)) {
            if (map.isWithinRange(province, i, maxDistance)) {
                if (isPriorityProvince(i)) {
                    std::cout << "Adding priority neighbor: " << cities[i] << std::endl;
                    queue.enqueuePriority(i);
                } else if (!isWeatherRestricted(i)) {
                    std::cout << "Adding non-priority neighbor: " << cities[i] << std::endl;
                    queue.enqueue(i);
                }
            } else {
                std::cout << "Neighbor " << cities[i] << " is out of range from " << cities[province] << std::endl;
            }
        } else {
            std::cout << "Neighbor " << cities[i] << " already visited or restricted." << std::endl;
        }
    }
}




// Backtracks if no further moves are possible
void RoutePlanner::backtrack() {
    std::cout << "Backtracking from: " << cities[stack.peek()] << std::endl;
    stack.pop();
    if (!stack.isEmpty()) {
        route.pop_back();
    } else {
        std::cout << "No more cities to backtrack to. Exploration ends." << std::endl;
    }
}



// Checks if exploration is complete
bool RoutePlanner::isExplorationComplete() const {
    return stack.isEmpty();
}

// Displays the final results of the journey
void RoutePlanner::displayResults() const {
    std::cout << "Journey Completed!" << std::endl;
    std::cout << "Total Provinces Visited: " << route.size() << std::endl;
    std::cout << "Total Distance Covered: " << totalDistanceCovered << " km" << std::endl;
    std::cout << "Route: ";
    for (int province : route) {
        std::cout << cities[province] << " ";
    }
    std::cout << std::endl;

    std::cout << "Priority Provinces Visited: ";
    for (int province : route) {
        if (isPriorityProvince(province)) {
            std::cout << cities[province] << " ";
        }
    }
    std::cout << std::endl;
}