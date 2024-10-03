// Copyright [2024] <exotic>
// CRUD (Create, Read, Update, Delete)

#ifndef CRUD_H_

#define CRUD_H_

#include "rent_management.h"

void ajouter(Car **, int *);
void menu(int *);
void affiche(Car *, int, int);
void affiche_tous_les_clients(Car *, int);
void modifier_voiture(Car *, int);
void supprimer_voiture(Car **, int *);
void save_to_file(Car *cars, int n, const char *filename);
void load_from_file(Car **cars, int *n, const char *filename);

#endif // !CRUD_H_
