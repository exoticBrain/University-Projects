#include <fstream>
#include <iostream>
#include <string>

struct Cellule {
  int Info;
  int Ind_L;
  int Ind_C;
  Cellule *Suiv_L;
  Cellule *Suiv_C;
};

typedef Cellule *TVect[10];

struct TMat {
  TVect TV, TVQ, TH, THQ;
  int Nb_L, Nb_C;
};

typedef TMat *PMat;

void Init_Mat(PMat &M);
void Creer_Mat(PMat &M, std::string Name);
void Afficher_Mat(PMat M);
void Liberer_Mat(PMat &M);
void Somme(PMat M1, PMat M2, PMat &M3);
