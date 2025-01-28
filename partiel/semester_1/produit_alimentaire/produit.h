#ifndef PRODUIT_H_

#define PRODUIT_H_

#include <string>
#include <iostream>

class Produit {

public:
  Produit(const int id);
  Produit(const int id, std::string label, float given_price);
  ~Produit();
  int get_ID();
  std::string get_label();
  float get_price();
  void set_ID(const int id);
  void set_label(std::string label);
  void set_price(float given_price);

private:
  const int ID;
  std::string Label;
  float price;
};

#endif // !PRODUIT_H_
