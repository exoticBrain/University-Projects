#include "produit.h"

Produit::Produit(const int id) : ID(id) {
  Label = "";
  price = 0;
}

Produit::Produit(const int id, std::string label, float given_price) : ID(id) {
  Label = label;
  price = given_price;
}

Produit::~Produit() {}

int Produit::get_ID() { return ID; }

std::string Produit::get_label() { return Label; }
float Produit::get_price() { return price; }
void Produit::set_label(std::string label) { Label = label; }
void Produit::set_price(float given_price) { price = given_price; }
