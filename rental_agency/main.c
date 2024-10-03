// Copyright [2024] <exotic>
#include "CRUD.h"

int main() {
  int menu_choice, number_of_cars;
  Car *cars;

  cars = NULL;
  menu_choice = 0;
  number_of_cars = 0;
  do {
    menu(&menu_choice);

    switch (menu_choice) {
    case 1:
      ajouter(&cars, &number_of_cars);
      break;
    case 2:
      if (cars)
        affiche(cars, number_of_cars, 1);
      else
        printf("No Car in the Garage\n");
      getch();
      break;
    case 3: {
      if (cars)
        modifier_voiture(cars, number_of_cars);
      else
        printf("No Car in the Garage\n");
      getch();
      break;
    }

    case 4: {
      if (!cars) {
        printf("No Car in the Garage\n");
        getch();
        break;
      }
      char matricul[20];
      printf("Veuillez saisir le numero d'immatriculation du Vehicule: ");
      scanf("%s", matricul);

      int car_index = rechercher_voiture(cars, number_of_cars, matricul);
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
      if (!cars) {
        printf("No Car in the Garage\n");
        getch();
        break;
      }
      supprimer_voiture(&cars, &number_of_cars);
      getch();
      break;
    }

    case 6: {
      if (!cars) {
        printf("No Car in the Garage\n");
        getch();
        break;
      }
      int count = 0;
      int current_year = 2024; // Use the actual current year
      for (int i = 0; i < number_of_cars; i++) {
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
      // remplir(cars, number_of_cars);
      printf("Not implemented yet!\n");
      getch();
      break;
    case 8:
      if (!cars) {
        printf("No Car in the Garage\n");
        getch();
        break;
      }
      affiche(cars, number_of_cars, 1);
      louer_voiture(cars, number_of_cars);
      getch();
      break;
    case 9:
      rendre_voiture(cars, number_of_cars);
      getch();
      break;
    case 10: {
      affiche_tous_les_clients(cars, number_of_cars);
      break;
    }
    case 11:
      printf("Goodbye\n");
      break;
    default:
      clear_screen();
      printf("Votre choix est incorrect\nEntrer un nombre de 1-11\n");
      getch();
      break;
    }
  } while (menu_choice != 11);
  // Free dynamically allocated memory before exiting
  if (cars != NULL) {
    free_memory(cars, number_of_cars);
  }
  return 0;
}
