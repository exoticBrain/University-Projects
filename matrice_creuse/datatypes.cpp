#include "datatypes.h"

std::string file_manipulation() {
  // get the filepath
  std::string filePath = "fichier_F.txt";

  // Open the file using ifstream
  std::ifstream file(filePath);

  // confirm file opening
  if (!file.is_open()) {
    // print error message and return
    std::cerr << "Failed to open file: " << filePath << std::endl;

    return NULL;
  }

  std::string line;
  getline(file, line);

  // Close the file
  file.close();

  std::cout << line << std::endl;
  return line;
}

