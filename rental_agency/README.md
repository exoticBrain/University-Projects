# 🚗 Car Rental System

## Overview

This project is a simple command-line car rental system written in C. It allows users to manage a fleet of cars, including adding new vehicles, renting cars, returning them, and managing rental periods. The system also maintains a list of renters for each car.

## Features 🌟

- `Add a car`: Dynamically add a new car to the system.
- `Modify a car`: Update details of existing cars.
- `Delete a car`: Remove a car from the system.
- `Rent a car`: Rent a car and manage rental periods with client waitlists.
- `Return a car`: Manage returns and synchronize with the next client on the waiting list.
- `Save/Load data`: Save the current state to a file and load from a file.

## Future Improvements 🚀

- Implement a GUI for a more user-friendly interface.
- Add reporting features (e.g., rental statistics, car availability trends).

## Requirements ⚙️

- GCC (GNU Compiler Collection)
- A Unix-like environment (Linux, macOS)

## Building the Project 🛠️

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

## File Structure 📁


- `main.c`:
The entry point of the application. It contains the main function and drives the entire project by managing the flow of the program. This file handles user input and provides a menu interface to access different functionalities, such as adding cars, renting cars, displaying car information, or saving/loading data.
- `CRUD.c`:
Implements the core operations required to manage cars in the system (Create, Read, Update, Delete - CRUD). This file includes functions to add new cars, modify existing cars, delete cars, display car information, and save/load car data to/from a file. It is a crucial part of the project for data management and persistence.
- `CRUD.h`:
Header file that declares the functions implemented in CRUD.c. It contains all the necessary function prototypes and any global constants or structures that the CRUD functions rely on.
- `rent_management.c`:
Focuses on handling the specific processes related to renting and returning cars. It includes validation logic to ensure that rental dates do not overlap, manages waiting lists for cars, and tracks rental periods. This file also makes use of various helper functions to enforce the rules of the rental system.
- `rent_management.h`:
The header file for the rent management module, containing function prototypes and definitions needed by the rental management functions in rent_management.c.
- `rent_system.h`:
Defines the key data structures used throughout the project, including Date, Person, and Car. These structures represent the fundamental components of the car rental system (e.g., car information, customer details, and rental periods). This file also declares utility functions that are implemented in tools.c.
tools.c:
A utility file that contains general helper functions used across multiple parts of the program. These helper functions provide additional support for input validation, comparison of dates, and other recurring tasks that are not specific to any one module.
- `build.sh`:
A shell script that automates the process of compiling the project. It uses the gcc compiler to build the source code into an executable, ensuring all necessary files are linked and compiled with the correct flags (-Wall -Wextra -Werror for catching potential issues). Running this script simplifies the build process for users.

## Memory Management 💾

The program dynamically allocates memory for cars and renters. It is essential to free all allocated memory before the program exits to prevent memory leaks. The `free_memory` function ensures that all dynamically allocated resources are released properly.

## Contributing 🤝

Contributions are welcome! If you have suggestions or improvements, feel free to create a pull request or open an issue.
