# Route Planner

Route Planner is a project designed to plan routes across various provinces in Türkiye. The system reads distance data, priority provinces, and weather-restricted provinces from files and explores routes based on these constraints.

## Project Overview

Route Planner is developed using C++ and provides a system for exploring routes across provinces while considering priority and weather-restricted provinces. The system uses stack and queue data structures to implement the route exploration algorithm.

### Features

The project includes:
1. **Distance Matrix**: Loads and stores distances between provinces.
2. **Priority Provinces**: Gives priority to certain provinces during route exploration.
3. **Weather-Restricted Provinces**: Avoids certain provinces due to weather restrictions.
4. **Route Exploration**: Explores routes using stack and queue data structures.
5. **Command Line Interface**: Reads input data from files and displays the results on the console.

## Technologies Used

- **C++**: The primary programming language used for developing the route planner system.

## Project Structure

The project structure includes several directories and files organized as follows:

- **`main.cpp`**: The main file that initializes the system and starts the route exploration.
- **`RoutePlanner.cpp`**: Implements the route exploration logic.
- **`RoutePlanner.h`**: Header file for `RoutePlanner.cpp`.
- **`Map.cpp`**: Manages the distance matrix and visited provinces.
- **`Map.h`**: Header file for `Map.cpp`.
- **`Queue.cpp`**: Implements a queue data structure.
- **`Queue.h`**: Header file for `Queue.cpp`.
- **`Stack.cpp`**: Implements a stack data structure.
- **`Stack.h`**: Header file for `Stack.cpp`.

## Usage

### Prerequisites

To run the project, you need to have the following installed:
- **C++ Compiler**: Ensure you have a C++ compiler installed on your system.

### Running the Project

1. Clone the repository:

    ```bash
    git clone https://github.com/barissolcay/route-planner.git
    cd route-planner
    ```

2. Compile the C++ files:

    ```bash
    g++ main.cpp RoutePlanner.cpp Map.cpp Queue.cpp Stack.cpp -o route-planner
    ```

3. Run the Route Planner with input files and parameters:

    ```bash
    ./route-planner <maxDistance> <startingCity> <distance_data> <priority_data> <restricted_data>
    ```

    Replace `<maxDistance>`, `<startingCity>`, `<distance_data>`, `<priority_data>`, and `<restricted_data>` with actual values and file paths.

## Contributing

We welcome contributions to improve the Route Planner project. Feel free to open issues or submit pull requests if you have suggestions for improvements or find any bugs.

## License

MIT License

```markdown
MIT License

Copyright (c) 2025 Baris Solcay

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
