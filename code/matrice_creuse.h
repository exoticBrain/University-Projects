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
void SommeMat(PMat M1, PMat M2, PMat &M3);
void Produit(PMat M1, PMat M2, PMat &M4);
void Puissance(PMat M, int K, PMat &Res);
void Sigma_Puissance(PMat M, int n, PMat &S);
