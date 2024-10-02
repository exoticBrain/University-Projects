// Copyright [2024] <exotic>
#include "rent_system.h"

void getch() {
  printf("\nPress Enter to continue...\n");
  getchar();
  getchar();
}

int rechercher_voiture(Car *cars, int n, const char *matricul) {
  for (int i = 0; i < n; i++) {
    if (strcmp(cars[i].matricul, matricul) == 0) {
      return i; // Return the index of the car
    }
  }
  return -1; // Return -1 if the car is not found
}

void trier_voitures(Car *cars, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      // Compare brands first
      int brand_comparison = strcmp(cars[j].brand, cars[j + 1].brand);

      // If brands are the same, compare models
      if (brand_comparison > 0 ||
          (brand_comparison == 0 && cars[j].model > cars[j + 1].model)) {
        // Swap the cars
        Car temp = cars[j];
        cars[j] = cars[j + 1];
        cars[j + 1] = temp;
      }
    }
  }
}

// Remplir les voitures
void remplir(Car *cars, int n) {
  for (int i = 0; i < n; i++) {
    printf("Car numero --> %d <--\n\n", i + 1);
    printf("Veuillez saisir le numero d'immatriculation : ");
    scanf("%s", cars[i].matricul);
    printf("Veuillez donner la marque du vehicule : ");
    scanf("%s", cars[i].brand);
    printf("Veuillez donner le modele du vehicule : ");
    scanf("%d", &cars[i].model);
    cars[i].is_rented = 0; // Initial state: not rented
    cars[i].renter_count = 0;
  }
  trier_voitures(cars, n);
}

// Ajouter une voiture
Car *ajouter(Car *cars, int *n) {
  Car new_car;

  printf("Veuillez saisir la marque du Vehicule: ");
  scanf("%s", new_car.brand);
  printf("Veuillez saisir le numero d'immatriculation: ");
  scanf("%s", new_car.matricul);
  printf("Veuillez saisir le model du Vehicule: ");
  scanf("%d", &new_car.model);

  new_car.is_rented = 0;
  new_car.renter_count = 0;

  // Reallocate memory for one additional car
  cars = realloc(cars, sizeof(Car) * (*n + 1));
  if (cars == NULL) {
    printf("Erreur lors de l'allocation de memoire.\n");
    exit(1); // Exit if memory allocation fails
  }

  cars[*n] = new_car; // Add new car at the end
  (*n)++;             // Increase number of cars
  trier_voitures(cars, *n);

  return cars; // Return the updated array
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

// Rendre une voiture
void rendre_voiture(Car *cars, int n) {
  char matricul[20];
  printf("Veuillez saisir le numero d'immatriculation du Vehicule que vous "
         "souhaitez rendre: ");
  scanf("%s", matricul);

  int car_index = rechercher_voiture(cars, n, matricul);
  if (car_index == -1) {
    printf("Voiture non trouvee.\n");
    return;
  }

  if (cars[car_index].is_rented == 0) {
    printf("Cette voiture n'est pas actuellement louee.\n");
    return;
  }

  // Complete the rental for the first person in the queue
  printf("Voiture rendue par %s %s.\n", cars[car_index].renters[0].first_name,
         cars[car_index].renters[0].last_name);

  // Shift all renters and dates (remove the first renter)
  for (int i = 0; i < cars[car_index].renter_count - 1; i++) {
    cars[car_index].renters[i] = cars[car_index].renters[i + 1];
    cars[car_index].rental_dates[i] = cars[car_index].rental_dates[i + 1];
  }

  cars[car_index].renter_count--;

  // If there are more people waiting, assign the car to the next person
  if (cars[car_index].renter_count > 0) {
    printf("La voiture est maintenant attribuee a %s %s pour la periode "
           "suivante.\n",
           cars[car_index].renters[0].first_name,
           cars[car_index].renters[0].last_name);
  } else {
    cars[car_index].is_rented = 0; // Car is now available
    printf("La voiture est maintenant disponible.\n");
  }
}

int supprimer_voiture(Car *cars, int n) {
  char matricul[20];
  printf("Veuillez saisir le numero d'immatriculation de la voiture à "
         "supprimer: ");
  scanf("%s", matricul);

  int car_index = rechercher_voiture(cars, n, matricul);
  if (car_index == -1) {
    printf("Voiture non trouvee.\n");
    return n;
  }

  // Shift the cars to "delete" the car at car_index
  for (int i = car_index; i < n - 1; i++) {
    cars[i] = cars[i + 1];
  }

  printf("Voiture supprimee avec succes.\n");
  return n - 1; // Decrease the number of cars
}

void free_memory(Car *cars, int n) {
  for (int i = 0; i < n; i++) {
    // If there are renters for this car, free their memory
    if (cars[i].renter_count > 0) {
      free(cars[i].renters);      // Free the memory allocated for renters
      free(cars[i].rental_dates); // Free the memory allocated for start dates
      free(cars[i].rental_dates_end); // Free the memory allocated for end dates
    }
  }

  // Free the memory allocated for the cars
  free(cars);
}
