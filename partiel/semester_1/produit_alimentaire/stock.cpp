#include "stock.h"
#include "produit_alimentaire.h"

Stock::Stock() { head = NULL; }

Stock::~Stock() { delete[] head; }

void Stock::ajouter_produit_alimentaire(const int id, std::string label,
                                        float given_price) {
  if (head == NULL) {
    ProduitAlimentaire *v1 = new ProduitAlimentaire(id);
    v1->set_label(label);
    v1->set_price(given_price);

    head = new List;
    head->info = v1;
    head->next = NULL;
  } else {
    List *q = head;
    bool exist = false;

    if (id == q->info->get_ID()) {
      exist = true;
    } else {
      while (q->next != NULL) {
        if (id == q->info->get_ID()) {
          exist = true;
          break;
        } else {
          q = q->next;
        }
      }
    }
    if (!exist) {
      ProduitAlimentaire *v1 = new ProduitAlimentaire(id);
      v1->set_label(label);
      v1->set_price(given_price);

      List *p = new List;
      p->next = NULL;
      p->info = v1;
      q->next = p;
    } else {
      std::cout << "Produit : " << id << " already exist !!\n";
    }
  }
}

void Stock::modifier_produit_alimentaire(const int id, std::string label,
                                         float given_price) {}

void Stock::supprimer_produit_alimentaire(const int id) {}

void Stock::lister_produit(Date today_date) {
  List *p = head;
  while (p != NULL) {
    std::cout << p->info->get_ID() << " " << p->info->get_label() << " "
              << p->info->get_price() << std::endl;
    p = p->next;
  }
}
