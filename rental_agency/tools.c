// Copyright [2024] <exotic>
#include "CRUD.h"
#include "rent_system.h"
#include <ctype.h>

void getch() {
  printf("\nPress Enter to continue...\n");
  getchar();
  getchar();
}

int valid_number(char *s) {
  while (*s) {
    if (!isdigit(*s))
      return 1;
    s++;
  }
  return -1;
}

void clear_screen() { system("clear"); }

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

void free_memory(Car *cars, int n) {
  for (int i = 0; i < n; i++) {
    // If there are renters for this car, free their memory
    if (cars[i].renter_count > 0) {
      free(cars[i].renters); // Free the memory allocated for renters
    }
  }

  // Free the memory allocated for the cars
  free(cars);
}

Car new_car(Car *cars, int n) {
  Car new_car;
  char mat[20];
  int valid_mat;
  do {
    printf("Veuillez saisir le numero d'immatriculation: ");
    scanf("%s", mat);
    valid_mat = rechercher_voiture(cars, n, mat);
    if (valid_mat != -1) {
      clear_screen();
      printf("Ce matricule est occupe\n");
      getch();
      clear_screen();
    }
  } while (valid_mat != -1);
  strcpy(new_car.matricul, mat);
  printf("Veuillez saisir la marque du Vehicule: ");
  scanf("%s", new_car.brand);

  char choix[20];
  int not_digit;
  do {
    printf("Veuillez saisir le model du Vehicule: ");
    scanf("%s", choix);
    not_digit = valid_number(choix);
    if (not_digit == 1) {
      clear_screen();
      printf("Entrer le model en nombre exemple ---> 2024\n");
      getch();
      clear_screen();
    }
  } while (not_digit == 1);

  new_car.model = atoi(choix);
  new_car.is_rented = 0;
  new_car.renter_count = 0;
  new_car.renters = NULL;

  return new_car;
}
