# Car Rental System

## Overview

This project is a simple command-line car rental system written in C. It allows users to manage a fleet of cars, including adding new vehicles, renting cars, returning them, and managing rental periods. The system also maintains a list of renters for each car.

## Features

- Add, modify, and delete cars from the system.
- Rent cars for specified periods, with validation for rental dates.
- Return cars and automatically update the availability.
- Maintain a waiting list for renters if a car is already rented.
- Display details of cars, including their rental status and current renters.

## Requirements

- GCC (GNU Compiler Collection)
- A Unix-like environment (Linux, macOS)

## Building the Project

To build the project, follow these steps:

1. Make the build script executable:
   ```bash
   chmod +x build.sh
2. Run the build script:
    ```bash
    ./build.sh
3. Execute the program:
    ```bash
    ./build/main

## File Structure

- `main.c`: Contains the main function and menu logic.
- `rent_system.c`: Implements the core functionality of the rental system.
- `renting_the_car.c`: Handles the rental and return processes.
- `displays.c`: Contains functions for displaying car information and details.

## Memory Management

The program dynamically allocates memory for cars and renters. It is essential to free all allocated memory before the program exits to prevent memory leaks. The `free_memory` function ensures that all dynamically allocated resources are released properly.

## Contributing

Contributions are welcome! If you have suggestions or improvements, feel free to create a pull request or open an issue.
