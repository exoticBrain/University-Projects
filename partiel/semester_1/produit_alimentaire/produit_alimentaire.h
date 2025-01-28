#ifndef PRODUIT_ALIMENTAIRE_H_
#define PRODUIT_ALIMENTAIRE_H_
#include "produit.h"

struct Date {
  int annee, mois, jour;
};

class ProduitAlimentaire : public Produit {
public:
    ProduitAlimentaire(const int id);
    ~ProduitAlimentaire();
    Date get_date();
    void set_date(int annee, int mois, int jour);
private:
    Date date_expiration;
};

#endif // !PRODUIT_ALIMENTAIRE_H_
