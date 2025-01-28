#include "produit_alimentaire.h"

ProduitAlimentaire::ProduitAlimentaire(const int id) : Produit(id) {}

ProduitAlimentaire::~ProduitAlimentaire() {}

Date ProduitAlimentaire::get_date() { return date_expiration; }

void ProduitAlimentaire::set_date(int annee, int mois, int jour) {
  date_expiration.annee = annee;
  date_expiration.mois = mois;
  date_expiration.jour = jour;
}
