#include "stock.h"

int main() {
  Stock s;
  Date dt;
  dt.annee = 2024;
  dt.mois = 1;
  dt.jour = 28;

  s.ajouter_produit_alimentaire(1, "test1", 12);
  s.ajouter_produit_alimentaire(2, "test2", 13);
  s.ajouter_produit_alimentaire(1, "test2", 13);
  s.ajouter_produit_alimentaire(4, "test2", 13);
  s.lister_produit(dt);
  return 0;
}
