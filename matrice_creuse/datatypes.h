#ifndef DATATYPES_H_
#define DATATYPES_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#define MAX 10

struct Cellule {
  int info, Ind_i, Ind_j;
  struct Cellule *suiv_L;
  struct Cellule *suiv_C;
};

typedef struct Cellule *PCellule;
typedef struct Cellule TVect[MAX];

struct TMat {
  TVect TV, TVQ, TH, THQ;
  int Nb_L, Nb_C;
};

typedef struct TMat *PMat;

std::string file_manipulation();

#endif // !DATATYPES_H_

