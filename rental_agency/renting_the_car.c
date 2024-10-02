// Copyright [2024] <exotic>
#include "rent_system.h"

int compare_dates(Date d1, Date d2) {
  if (d1.year != d2.year)
    return d1.year - d2.year;
  if (d1.month != d2.month)
    return d1.month - d2.month;
  return d1.day - d2.day;
}

int check_date_overlap(Date start1, Date end1, Date start2, Date end2) {
  // Return true if date ranges overlap
  if (compare_dates(start1, end2) > 0 || compare_dates(start2, end1) > 0) {
    return 0; // No overlap
  }
  return 1; // Overlapping
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
  if (car->is_rented) {
    printf("La voiture est actuellement louee. Souhaitez-vous rejoindre la "
           "liste d'attente ? (1-Oui, 0-Non): ");
    int choix;
    scanf("%d", &choix);
    if (choix == 0)
      return;
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
    printf("Veuillez saisir la date de debut de location (AAAA MM JJ): ");
    scanf("%d %d %d", &start_date.year, &start_date.month, &start_date.day);
    printf("Veuillez saisir la date de fin de location (AAAA MM JJ): ");
    scanf("%d %d %d", &end_date.year, &end_date.month, &end_date.day);

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
