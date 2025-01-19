#include "datatypes.h"

int main() {
  std::string line = file_manipulation();
  char *matrix = strtok((char *)line.c_str(), " ");

  int line_number = atoi(matrix);
  // take subsequent tokens
  matrix = strtok(NULL, " ");

  int colonne_number = atoi(matrix);
  // take subsequent tokens
  matrix = strtok(NULL, " ");

  std::cout << "line : " << line_number << std::endl;
  std::cout << "colonne : " << colonne_number << std::endl;
  while (matrix) {

    // take subsequent tokens
    matrix = strtok(NULL, " ");
  }
}
