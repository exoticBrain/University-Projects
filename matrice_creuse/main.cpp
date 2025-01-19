#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  // get the filepath
  string filePath = "fichier_F.txt";

  // Open the file using ifstream
  ifstream file(filePath);

  // confirm file opening
  if (!file.is_open()) {
    // print error message and return
    cerr << "Failed to open file: " << filePath << endl;

    return 1;
  }

  string line;
  getline(file, line);

  char *matrix = strtok((char *)line.c_str(), " ");

  int line_number = atoi(matrix);
  // take subsequent tokens
  matrix = strtok(NULL, " ");

  int colonne_number = atoi(matrix);
  // take subsequent tokens
  matrix = strtok(NULL, " ");

  cout << "line : " << line_number << endl;
  cout << "colonne : " << colonne_number << endl;
  while (matrix) {

    // take subsequent tokens
    matrix = strtok(NULL, " ");
  }

  // Close the file
  file.close();
}
