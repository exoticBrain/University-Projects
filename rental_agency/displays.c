// Copyright [2024] <exotic>
#include "rent_system.h"

void menu() {
  system("clear");
  printf("\n\t\t\t\t   MENU\n\t\t\t\t --------\n\n\n"
         "1-Ajouter une Vehicule\t\t\t"
         "2-Afficher Les Vehicules\n\n"
         "3-Modifier une Vehicule\t\t\t"
         "4-Rechercher une Vehicule par son numero d'immatriculation\n\n"
         "5-Supprimer une Vehicule\t\t"
         "6-Le nombre de Vehicules > 10 ans\n\n"
         "7-Remplir\t\t\t\t"
         "8-Louer une voiture\n\n"
         "9-Rendre une voiture\t\t\t"
         "10-Afficher tous les clients et leurs periodes de location\n\n"
         "11-Quitter\n\n"
         "Votre choix --> ");
}

// Afficher les voitures
void affiche(Car *cars, int n, int numero_flag) {
  for (int i = 0; i < n; i++) {
    if (numero_flag)
      printf("Vehicule numero --> %d <--\n", i + 1);
    printf("Marque : %s\n", cars[i].brand);
    printf("Numero d'immatriculation : %s\n", cars[i].matricul);
    printf("Model : %d\n", cars[i].model);
    printf("Disponibilite : %s\n",
           cars[i].is_rented ? "Non disponible" : "Disponible");

    // If the car is rented, display rental information
    if (cars[i].renter_count > 0) {
      printf("Actuellement louee par : %s %s (CIN: %s)\n",
             cars[i].renters[0].first_name, cars[i].renters[0].last_name,
             cars[i].renters[0].cin);
      printf("Periode de location actuelle : du %d/%d/%d au %d/%d/%d\n",
             cars[i].rental_dates[0].year, cars[i].rental_dates[0].month,
             cars[i].rental_dates[0].day, cars[i].rental_dates_end[0].year,
             cars[i].rental_dates_end[0].month,
             cars[i].rental_dates_end[0].day);

      // If there are more renters in the waiting list, show them
      if (cars[i].renter_count > 1) {
        printf("Prochains locataires en attente :\n");
        for (int j = 1; j < cars[i].renter_count; j++) {
          printf("Client %d: %s %s (CIN: %s)\n", j + 1,
                 cars[i].renters[j].first_name, cars[i].renters[j].last_name,
                 cars[i].renters[j].cin);
          printf("Periode de location : du %d/%d/%d au %d/%d/%d\n",
                 cars[i].rental_dates[j].year, cars[i].rental_dates[j].month,
                 cars[i].rental_dates[j].day, cars[i].rental_dates_end[j].year,
                 cars[i].rental_dates_end[j].month,
                 cars[i].rental_dates_end[j].day);
        }
      }
    } else {
      printf("La voiture est disponible.\n");
    }

    printf("________________\n\n");
  }
}

void affiche_tous_les_clients(Car *cars, int n) {
  int found_clients = 0;
  for (int i = 0; i < n; i++) {
    if (cars[i].renter_count > 0) {
      printf("\nVoiture %d: %s (Numero d'immatriculation: %s)\n", i + 1,
             cars[i].brand, cars[i].matricul);
      for (int j = 0; j < cars[i].renter_count; j++) {
        printf("Locataire %d: %s %s (CIN: %s)\n", j + 1,
               cars[i].renters[j].first_name, cars[i].renters[j].last_name,
               cars[i].renters[j].cin);
        printf("Periode de location: du %d/%d/%d au %d/%d/%d\n",
               cars[i].rental_dates[j].year, cars[i].rental_dates[j].month,
               cars[i].rental_dates[j].day, cars[i].rental_dates_end[j].year,
               cars[i].rental_dates_end[j].month,
               cars[i].rental_dates_end[j].day);
      }
      found_clients = 1;
    }
  }

  if (!found_clients) {
    printf("Aucun client n'a loue de voitures pour le moment.\n");
  }

  getch(); // Wait for user input
}
