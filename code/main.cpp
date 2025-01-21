#include "matrice_creuse.h"



int main()
{
    PMat M1 = NULL;

    // Question 1
    Creer_Mat(M1, "name.txt");

    // Question 4
    Afficher_Mat(M1);

    Liberer_Mat(M1);

    return 0;
}
