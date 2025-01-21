#include "matrice_creuse.h"

void Init_Mat(PMat& M)
{
    M = new TMat;

    M->Nb_L = 0;
    M->Nb_C = 0;

    for (int i = 0; i < 10; i++)
    {
        M->TV[i] = NULL;
        M->TVQ[i] = NULL;
        M->TH[i] = NULL;
        M->THQ[i] = NULL;
    }
    std::cout << "Matix has been initialized...." << std::endl;
}

void Creer_Mat(PMat& M, std::string Name)
{
    std::ifstream fichier(Name);

    if (!fichier.is_open())
    {
        std::cout << "erreur d'ouverture de : " << Name << std::endl;
        return;
    }

    Init_Mat(M);

    fichier >> M->Nb_L >> M->Nb_C;

    for (int i = 0; i < M->Nb_L; i++)
    {
        Cellule* p1 = NULL;

        for (int j = 0; j < M->Nb_C; j++)
        {
            int v;
            fichier >> v;

            Cellule* nv = new Cellule;
            nv->Info = v;
            nv->Ind_L = i;
            nv->Ind_C = j;
            nv->Suiv_C = NULL;

            // Ajouter la cellule dans le vecteur TV
            if (M->TV[i] == NULL)
            {
                M->TV[i] = nv;
            }
            else
            {
                p1->Suiv_C = nv;
            }
            p1 = nv;
        }
    }

    fichier.close();
    std::cout << "Q1 ) matrice creee a partir du fichier : " << Name << std::endl;
}

//question 4
void Afficher_Mat(PMat M)
{
    if (M != NULL)
    {
        std::cout <<"Q4 )" << std::endl;
        for (int i = 0; i < M->Nb_L; i++)
        {
            Cellule* p2 = M->TV[i];
            while (p2 != NULL)
            {
                std::cout << p2->Info << " ";
                p2 = p2->Suiv_C;
            }
            std::cout << std::endl;
        }
    }
}

void Liberer_Mat(PMat& M)
{
    if (M != NULL)
    {
        for (int i = 0; i < M->Nb_L; i++)
        {
            Cellule* p3 = M->TV[i];

            while (p3 != NULL)
            {
                // Stocke un pointeur vers la cellule suivante avant de supprimer la cellule actuelle
                Cellule* psuiv = p3->Suiv_C;

                // Libère la mémoire de la cellule actuelle
                delete p3;

                // Passe à la cellule suivante
                p3 = psuiv;
            }
        }

        delete M;

        // Met le pointeur de la matrice à NULL pour éviter les accès invalides
        M = NULL;

        std::cout << "Q3 ) matrice liberee" << std::endl;
    }
}


