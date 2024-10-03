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
  (*cars)[*n] = new_car(*cars, *n);
  (*n)++; // Increase number of cars
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
         "11-Sauvegarder dans un fichier\t\t"
         "12-Charger depuis un fichier\n\n"
         "13-Quitter\n\n"
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
      printf("Actuellement louee par : \n>---------\nPrenom: %s\nNom: %s\nCIN: "
             "%s\n",
             cars[i].renters[0].first_name, cars[i].renters[0].last_name,
             cars[i].renters[0].cin);
      printf(
          "Periode de location actuelle : du %d/%d/%d au %d/%d/%d\n---------\n",
          cars[i].renters[0].start_date.year,
          cars[i].renters[0].start_date.month,
          cars[i].renters[0].start_date.day, cars[i].renters[0].end_date.year,
          cars[i].renters[0].end_date.month, cars[i].renters[0].end_date.day);

      // If there are more renters in the waiting list, show them
      if (cars[i].renter_count > 1) {
        printf("Prochains locataires en attente :\n");
        for (int j = 1; j < cars[i].renter_count; j++) {
          printf("Client %d: \n>---------\nPrenom: %s\nNom: %s\nCIN: %s\n",
                 j + 1, cars[i].renters[j].first_name,
                 cars[i].renters[j].last_name, cars[i].renters[j].cin);
          printf("Periode de location : du %d/%d/%d au %d/%d/%d\n---------\n",
                 cars[i].renters[j].start_date.year,
                 cars[i].renters[j].start_date.month,
                 cars[i].renters[j].start_date.day,
                 cars[i].renters[j].end_date.year,
                 cars[i].renters[j].end_date.month,
                 cars[i].renters[j].end_date.day);
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
        printf(
            "Periode de location: du %d/%d/%d au %d/%d/%d\n",
            cars[i].renters[j].start_date.year,
            cars[i].renters[j].start_date.month,
            cars[i].renters[j].start_date.day, cars[i].renters[j].end_date.year,
            cars[i].renters[j].end_date.month, cars[i].renters[j].end_date.day);
      }
      found_clients = 1;
    }
  }

  if (!found_clients) {
    printf("Aucun client n'a loue de voitures pour le moment.\n");
  }

  getch(); // Wait for user input
}

void save_to_file(Car *cars, int n, const char *filename) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    printf("Erreur: Impossible d'ouvrir le fichier pour la sauvegarde.\n");
    return;
  }

  // Save the number of cars
  fprintf(file, "%d\n", n);

  // Save each car's information
  for (int i = 0; i < n; i++) {
    fprintf(file, "%s %s %d %d\n", cars[i].matricul, cars[i].brand,
            cars[i].model, cars[i].renter_count);

    // Save rental information if the car is rented
    for (int j = 0; j < cars[i].renter_count; j++) {
      fprintf(
          file, "%s %s %s %d/%d/%d %d/%d/%d\n", cars[i].renters[j].first_name,
          cars[i].renters[j].last_name, cars[i].renters[j].cin,
          cars[i].renters[j].start_date.year,
          cars[i].renters[j].start_date.month,
          cars[i].renters[j].start_date.day, cars[i].renters[j].end_date.year,
          cars[i].renters[j].end_date.month, cars[i].renters[j].end_date.day);
    }
  }

  fclose(file);
  printf("Données sauvegardées avec succès dans le fichier %s.\n", filename);
  getch();
}

void load_from_file(Car **cars, int *n, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Erreur: Impossible d'ouvrir le fichier pour le chargement.\n");
    return;
  }

  // Free previously allocated memory if necessary
  if (*cars != NULL) {
    free(*cars);
  }

  // Load the number of cars
  fscanf(file, "%d", n);

  // Allocate memory for the cars
  *cars = (Car *)malloc(sizeof(Car) * (*n));
  if (*cars == NULL) {
    printf("Erreur lors de l'allocation de mémoire pour les voitures.\n");
    fclose(file);
    return;
  }

  // Load each car's information
  for (int i = 0; i < *n; i++) {
    fscanf(file, "%s %s %d %d", (*cars)[i].matricul, (*cars)[i].brand,
           &(*cars)[i].model, &(*cars)[i].renter_count);

    // Allocate memory for the renters
    (*cars)[i].renters =
        (Person *)malloc(sizeof(Person) * (*cars)[i].renter_count);
    if ((*cars)[i].renters == NULL) {
      printf("Erreur lors de l'allocation de mémoire pour les locataires.\n");
      fclose(file);
      return;
    }

    // Load the renters and their rental periods
    for (int j = 0; j < (*cars)[i].renter_count; j++) {
      fscanf(file, "%s %s %s %d/%d/%d %d/%d/%d",
             (*cars)[i].renters[j].first_name, (*cars)[i].renters[j].last_name,
             (*cars)[i].renters[j].cin, &(*cars)[i].renters[j].start_date.year,
             &(*cars)[i].renters[j].start_date.month,
             &(*cars)[i].renters[j].start_date.day,
             &(*cars)[i].renters[j].end_date.year,
             &(*cars)[i].renters[j].end_date.month,
             &(*cars)[i].renters[j].end_date.day);
    }
  }

  fclose(file);
  printf("Données chargées avec succès depuis le fichier %s.\n", filename);
  getch();
}
