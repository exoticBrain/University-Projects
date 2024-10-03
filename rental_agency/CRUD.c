// Copyright [2024] <exotic>
#include "CRUD.h"
#include "rent_system.h"

void ajouter(Car **cars, int *n) {
  if (*n == 0) {
    *cars = (Car *)malloc(sizeof(Car));
    if (*cars == NULL) {
      printf("Erreur lors de l'allocation de memoire. 'malloc in ajouter()'\n");
      exit(1); // Exit if memory allocation fails
    }
  } else {
    *cars = (Car *)realloc(*cars, sizeof(Car) * ((*n + 1)));
    if (*cars == NULL) {
      printf(
          "Erreur lors de l'allocation de memoire. 'realloc in ajouter()'\n");
      exit(1); // Exit if memory allocation fails
    }
  }

  *cars[*n] = new_car(*cars, *n); // Add new car at the end
  (*n)++;                         // Increase number of cars
  trier_voitures(*cars, *n);
}

void modifier_voiture(Car *cars, int n) {
  char matricul[20];
  printf("Veuillez saisir le numero d'immatriculation du Vehicule que vous "
         "souhaitez modifier: ");
  scanf("%s", matricul);

  int car_index = rechercher_voiture(cars, n, matricul);
  if (car_index == -1) {
    printf("Voiture non trouvee.\n");
    return;
  }

  // Show current details of the car
  printf("Voiture trouvee:\n");
  printf("Marque actuelle: %s\n", cars[car_index].brand);
  printf("Modele actuel: %d\n", cars[car_index].model);
  printf("Immatriculation actuelle: %s\n", cars[car_index].matricul);

  // Modify car details
  printf("\nModification des details de la voiture:\n");

  printf("Nouvelle marque (type 'skip' pour ne pas modifier): ");
  char new_brand[20];
  scanf("%s", new_brand);
  if (strlen(new_brand) > 0 && strcmp(new_brand, "skip") != 0) {
    strcpy(cars[car_index].brand, new_brand);
  }

  printf("Nouveau modele (0 pour ne pas modifier): ");
  int new_model;
  scanf("%d", &new_model);
  if (new_model > 0) {
    cars[car_index].model = new_model;
  }

  printf("Nouvelle immatriculation (type 'skip' pour ne pas modifier): ");
  char new_matricul[20];
  scanf("%s", new_matricul);
  if (strlen(new_matricul) > 0 && strcmp(new_matricul, "skip") != 0) {
    strcpy(cars[car_index].matricul, new_matricul);
  }

  printf("Modification terminee.\n");
}

void supprimer_voiture(Car **cars, int *n) {
  char matricul[20];
  printf("Veuillez saisir le numero d'immatriculation de la voiture à "
         "supprimer: ");
  scanf("%s", matricul);

  int car_index = rechercher_voiture(*cars, *n, matricul);
  if (car_index == -1) {
    printf("Voiture non trouvee.\n");
    return;
  }

  // Shift the cars to "delete" the car at car_index
  for (int i = car_index; i < *n - 1; i++) {
    *cars[i] = *cars[i + 1];
  }

  printf("Voiture supprimee avec succes.\n");
  (*n)--;
  *cars = realloc(*cars, sizeof(Car) * (*n));
  if (*cars == NULL) {
    printf("Erreur lors de l'allocation de memoire. 'realloc in "
           "supprimer_voiture()'\n");
    exit(1); // Exit if memory allocation fails
  }
}

void menu(int *choix) {
  clear_screen();
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
  scanf("%d", choix);
  clear_screen();
}

void affiche(Car *cars, int n, int numero_flag) {
  for (int i = 0; i < n; i++) {
    if (numero_flag)
      printf("Vehicule numero --> %d <--\n", i + 1);
    printf("Marque : %s\n", cars[i].brand);
    printf("Numero d'immatriculation : %s\n", cars[i].matricul);
    printf("Model : %d\n", cars[i].model);

    // If the car is rented, display rental information
    if (cars[i].renter_count > 0) {
      printf("Actuellement louee par : Prenom: %s\nNom: %s\nCIN: %s\n",
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
          printf("Client %d: Prenom: %s\nNom: %s\nCIN: %s\n", j + 1,
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
