#ifndef STOCK_H_

#define STOCK_H_

#include "produit_alimentaire.h"

struct List {
  ProduitAlimentaire *info;
  List *next;
};

class Stock {
private:
  List *head;

public:
  Stock();
  ~Stock();
  void ajouter_produit_alimentaire(const int id, std::string label,
                                   float given_price);
  void modifier_produit_alimentaire(const int id, std::string label,
                                    float given_price);
  void supprimer_produit_alimentaire(const int id);
  void lister_produit(Date today_date);
};

#endif // !STOCK_H_
