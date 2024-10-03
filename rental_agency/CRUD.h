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

#endif // !CRUD_H_
