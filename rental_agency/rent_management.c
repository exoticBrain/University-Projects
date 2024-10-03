// Copyright [2024] <exotic>
#include "rent_management.h"
#include "rent_system.h"

int valid_year() {
  int year;
  printf("Annee : ");
  do {
    scanf("%d", &year);
    if (year < 2024 || year > 2035) {
      printf("pour de vrai, tu vas le louer pour cette annee\n");
      printf("choisir une annee superieure a 2024 et moins de 2035\n--> ");
    }
  } while (year < 2024 || year > 2035);

  return year;
}

int valid_month() {
  int month;
  printf("Mois : ");
  do {
    scanf("%d", &month);
    if (month < 1 || month > 12) {
      printf("pour de vrai, tu vas le louer pour ce mois\n");
      printf("choisir un mois superieure a 1 et moins de 12\n--> ");
    }
  } while (month < 1 || month > 12);

  return month;
}

int valid_day() {
  int day;
  printf("Jour : ");
  do {
    scanf("%d", &day);
    if (day < 1 || day > 30) {
      printf("pour de vrai, tu vas le louer pour ce jour\n");
      printf("choisir un jour superieure a 1 et moins de 30\n--> ");
    }
  } while (day < 1 || day > 30);

  return day;
}

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
  int choix = 0;
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
  } else {
    car->renters = (Person *)malloc(sizeof(Person));
  }

  if (choix)
    car->renters = (Person *)realloc(car->renters,
                                     sizeof(Person) * (car->renter_count + 1));
  // Get the rental period with validation
  Date start_date, end_date;
  int valid_dates = 0;

  while (!valid_dates) {
    printf("Veuillez saisir la date de debut de location : \n");
    start_date.year = valid_year();
    start_date.month = valid_month();
    start_date.day = valid_day();

    printf("Veuillez saisir la date de fin de location : \n");
    end_date.year = valid_year();
    end_date.month = valid_month();
    end_date.day = valid_day();

    // Check if the end date is after the start date
    if (end_date.year > start_date.year ||
        (end_date.year == start_date.year &&
         end_date.month > start_date.month) ||
        (end_date.year == start_date.year &&
         end_date.month == start_date.month &&
         end_date.day >= start_date.day)) {
      // Now we check if the new rental period overlaps with existing rentals
      int overlap_found = 0;
      for (int i = 0; i < car->renter_count; i++) {
        if (check_date_overlap(start_date, end_date, car->renters[i].start_date,
                               car->renters[i].end_date)) {
          overlap_found = 1;
          break;
        }
      }

      if (overlap_found) {
        printf("Cette voiture est déjà louée pour cette période. Veuillez "
               "choisir une autre période.\n");
      } else {
        valid_dates = 1; // Dates are valid and not overlapping
      }
    } else {
      printf("Erreur: La date de fin doit être postérieure ou égale à la date "
             "de début. Veuillez réessayer.\n");
    }
  }

  // Ask for the renter's details
  Person renter;
  printf("Veuillez saisir le nom du locataire: ");
  scanf("%s", renter.first_name);
  printf("Veuillez saisir le prenom du locataire: ");
  scanf("%s", renter.last_name);
  printf("Veuillez saisir le CIN du locataire: ");
  scanf("%s", renter.cin);

  // Store the renter's information and the rental period
  int renter_pos = car->renter_count;
  car->renters[renter_pos] = renter;
  car->renters[renter_pos].start_date = start_date;
  car->renters[renter_pos].end_date = end_date;
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
  }

  cars[car_index].renter_count--;

  // If there are more people waiting, assign the car to the next person
  if (cars[car_index].renter_count > 0) {
    printf("La voiture est maintenant attribuee a %s %s pour la periode ",
           cars[car_index].renters[0].first_name,
           cars[car_index].renters[0].last_name);
    printf("de location suivante : du %d/%d/%d au %d/%d/%d\n---------\n",
           cars[car_index].renters[0].start_date.year,
           cars[car_index].renters[0].start_date.month,
           cars[car_index].renters[0].start_date.day,
           cars[car_index].renters[0].end_date.year,
           cars[car_index].renters[0].end_date.month,
           cars[car_index].renters[0].end_date.day);
  } else {
    cars[car_index].is_rented = 0; // Car is now available
    printf("La voiture est maintenant disponible.\n");
  }
}
