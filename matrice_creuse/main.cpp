#include "datatypes.h"

int main() {

    PMat M1, M2, M3, M4, S, Res;
  std::string line = file_manipulation();

  // --- Splitting the numbers into tokens of chars
  char *matrix = strtok((char *)line.c_str(), " ");

  // --- Getting the line and column numbers
  int line_number = atoi(matrix);
  matrix = strtok(NULL, " ");

  int column_number = atoi(matrix);
  matrix = strtok(NULL, " ");

  std::cout << "line : " << line_number << std::endl;
  std::cout << "colonne : " << column_number << std::endl;
  while (matrix) {
    for (int i = 0; i < line_number; i++) {
      for (int j = 0; j < column_number; j++) {
      }
    }
    // take subsequent tokens
    matrix = strtok(NULL, " ");
  }
}
