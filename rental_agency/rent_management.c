// Copyright [2024] <exotic>
#include "rent_management.h"

int valid_year() {
  int year;
  printf("Annee : \n");
  do {
    scanf("%d", &year);
  } while (year < 2024);

  return year;
}

int valid_month() {
  int month;
  printf("Mois : \n");
  do {
    scanf("%d", &month);
  } while (month < 1 || month > 12);

  return month;
}

int valid_day() {
  int day;
  printf("Jour : \n");
  do {
    scanf("%d", &day);
  } while (day < 1 || day > 30);

  return day;
}

void louer_voiture(Car *cars, int n) {
  char matricul[20];
  printf("Veuillez saisir le numero d'immatriculation de la voiture que vous "
         "souhaitez louer: ");
  scanf("%s", matricul);

  // Find the car by its matricul number
  int car_index = rechercher_voiture(cars, n, matricul);
  if (car_index == -1) {
    printf("Voiture non trouvee.\n");
    return;
  }

  Car *car = &cars[car_index];

  // Check if the car is already rented
  int choix;
  if (car->is_rented) {
    printf("La voiture est actuellement louee. Souhaitez-vous rejoindre la "
           "liste d'attente ? (1-Oui, 0-Non): ");
    do {
      scanf("%d", &choix);
      if (choix == 0)
        return;
      if (choix != 1 && choix != 0)
        printf("Enter le nombre: 1 ou 2\n");
    } while (choix > 1 || choix < 0);
  }

  // Ask for the renter's details
  Person renter;
  printf("Veuillez saisir le nom du locataire: ");
  scanf("%s", renter.first_name);
  printf("Veuillez saisir le prenom du locataire: ");
  scanf("%s", renter.last_name);
  printf("Veuillez saisir le CIN du locataire: ");
  scanf("%s", renter.cin);

  // Get the rental period with validation
  Date start_date, end_date;
  int valid_dates = 0;

  while (!valid_dates) {
    printf("Veuillez saisir la date de debut de location : ");
    start_date.year = valid_year();
    start_date.month = valid_month();
    start_date.day = valid_day();
    printf("Veuillez saisir la date de fin de location : ");
    end_date.year = valid_year();
    end_date.month = valid_month();
    end_date.day = valid_day();

    // Check if the end date is later than the start date
    if (end_date.year > start_date.year ||
        (end_date.year == start_date.year &&
         end_date.month > start_date.month) ||
        (end_date.year == start_date.year &&
         end_date.month == start_date.month &&
         end_date.day >= start_date.day)) {
      valid_dates = 1;
    } else {
      printf("Erreur: La date de fin doit etre posterieure ou egale a la date "
             "de debut. Veuillez reessayer.\n");
    }
  }

  // Store the renter's information and the rental period
  int renter_pos = car->renter_count;
  car->renters[renter_pos] = renter;
  car->rental_dates[renter_pos] = start_date;
  car->rental_dates_end[renter_pos] = end_date;
  car->renter_count++;

  // Mark the car as rented
  car->is_rented = 1;

  printf("La voiture a ete louee avec succes du %d/%d/%d au %d/%d/%d.\n",
         start_date.year, start_date.month, start_date.day, end_date.year,
         end_date.month, end_date.day);
}

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
