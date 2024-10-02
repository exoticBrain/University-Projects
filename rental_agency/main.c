// Copyright [2024] <exotic>
#include "rent_system.h"

int main() {
  int choix, n;
  Car *cars = NULL;

  system("clear");
  printf("Donner le nombre de voitures dans le garage: ");
  scanf("%d", &n);
  system("clear");

  cars = malloc(sizeof(Car) * n);

  int remplir_first;
  if (n) {
    printf("Voulez-vous remplir les voitures deja existantes dans le garage\n");
    do {
      printf("\n1-Yes\n2-No\n--> ");
      scanf("%d", &remplir_first);
    } while (remplir_first < 1 || remplir_first > 2);

    if (remplir_first == 1) {
      remplir(cars, n);
    }
  }

  do {
    system("clear");
    menu();
    scanf("%d", &choix);
    system("clear");

    switch (choix) {
    case 1:
      cars = ajouter(cars, &n);
      break;

      break;
    case 2:
      if (*cars->brand)
        affiche(cars, n, 1);
      else
        printf("No Car in the Garage\n");
      getch();
      break;
    case 3: {
      if (*cars->brand)
        modifier_voiture(cars, n);
      else
        printf("No Car in the Garage\n");
      getch();
      break;
    }

    case 4: {
      if (!*cars->brand) {
        printf("No Car in the Garage\n");
        getch();
        break;
      }
      char matricul[20];
      printf("Veuillez saisir le numero d'immatriculation du Vehicule: ");
      scanf("%s", matricul);

      int car_index = rechercher_voiture(cars, n, matricul);
      if (car_index != -1) {
        printf("Voiture trouvee :\n");
        printf("Marque: %s\n", cars[car_index].brand);
        printf("Modele: %d\n", cars[car_index].model);
        printf("Immatriculation: %s\n", cars[car_index].matricul);
      } else {
        printf("Voiture non trouvee.\n");
      }
      getch();
      break;
    }
    case 5: {
      if (!*cars->brand) {
        printf("No Car in the Garage\n");
        getch();
        break;
      }
      n = supprimer_voiture(cars, n);
      getch();
      break;
    }

    case 6: {
      if (!*cars->brand) {
        printf("No Car in the Garage\n");
        getch();
        break;
      }
      int count = 0;
      int current_year = 2024; // Use the actual current year
      for (int i = 0; i < n; i++) {
        if (current_year - cars[i].model > 5) {
          affiche(&cars[i], 1, 0);
          count++;
        }
      }
      printf("Nombre de Vehicules de plus de 5 ans: %d\n", count);
      getch();
      break;
    }
    case 7:
      remplir(cars, n);
      getch();
    case 8:
      if (!*cars->brand) {
        printf("No Car in the Garage\n");
        getch();
        break;
      }
      louer_voiture(cars, n);
      getch();
      break;
    case 9:
      rendre_voiture(cars, n);
      getch();
      break;
    case 10: {
      affiche_tous_les_clients(cars, n);
      break;
    }

    case 11:
      printf("Goodbye\n");
      break;
    default:
      break;
    }
  } while (choix != 11);
  // Free dynamically allocated memory before exiting
  if (cars != NULL) {
    free_memory(cars, n);
  }
  return 0;
}
