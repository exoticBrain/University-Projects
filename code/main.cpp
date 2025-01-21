#include "matrice_creuse.h"

int main() {
  PMat M1 = NULL;
  PMat M2 = NULL;
  PMat M3 = NULL;
  PMat M4 = NULL;
  PMat S = NULL;
  PMat Res = NULL;

  // Create and display matrices M1 and M2
  Creer_Mat(M1, "name.txt");
  Afficher_Mat(M1);
  Creer_Mat(M2, "name2.txt");
  Afficher_Mat(M2);
  // Sum of M1 and M2 into M3
  SommeMat(M1, M2, M3);
  Afficher_Mat(M3);
  // Product of M1 and M2 into M4
  Produit(M1, M2, M4);
  Afficher_Mat(M4);

/*
  // Power of M1 (e.g., M1^2) into Res
  int k = 2; // Example power
  Puissance(M1, k, Res);
  Afficher_Mat(Res);

  // Sum of powers of M1 up to n (e.g., M1 + M1^2 + ... + M1^n) into S
  int n = 3; // Example number of terms
  Sigma_Puissance(M1, n, S);
  Afficher_Mat(S);

*/
  // Free all allocated memory
  Liberer_Mat(M1);
  Liberer_Mat(M2);
  Liberer_Mat(M3);
  Liberer_Mat(M4);
/*
  Liberer_Mat(Res);
  Liberer_Mat(S);
*/

  return 0;
}

