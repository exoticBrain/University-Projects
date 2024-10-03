// Copyright [2024] <exotic>
#ifndef RENT_SYSTEM_H

#define RENT_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int year;
  int month;
  int day;
} Date;

typedef struct {
  char first_name[20];
  char last_name[20];
  char cin[20];
  int waiting_number; // Number for waiting if the car is already rented
  int return_day;     // When the car will be available (simplified)
} Person;

typedef struct {
  char matricul[20];
  int model;
  char brand[20];
  Person renters[10];        // Stores up to 10 clients
  Date rental_dates[10];     // Start dates for each client
  Date rental_dates_end[10]; // End dates for each client
  int renter_count;          // Number of clients renting this car
  int is_rented;             // 0 if not rented, 1 if rented
} Car;

void getch();
void clear_screen();
void trier_voitures(Car *cars, int n);
Car new_car(Car *cars, int n);
void get_number_of_cars(int *);
int rechercher_voiture(Car *cars, int n, const char *matricul);
void trier_voitures(Car *cars, int n);
int compare_dates(Date d1, Date d2);
int check_date_overlap(Date start1, Date end1, Date start2, Date end2);
void free_memory(Car *cars, int n);

#endif // !RENT_SYSTEM_H
