#include "matrice_creuse.h"

void Init_Mat(PMat &M) {
  M = new TMat;

  M->Nb_L = 0;
  M->Nb_C = 0;

  for (int i = 0; i < 10; i++) {
    M->TV[i] = NULL;
    M->TVQ[i] = NULL;
    M->TH[i] = NULL;
    M->THQ[i] = NULL;
  }
  std::cout << "Matix has been initialized...." << std::endl;
}

void Creer_Mat(PMat &M, std::string Name) {
  std::ifstream fichier(Name);

  if (!fichier.is_open()) {
    std::cout << "erreur d'ouverture de : " << Name << std::endl;
    return;
  }

  Init_Mat(M);

  fichier >> M->Nb_L >> M->Nb_C;

  for (int i = 0; i < M->Nb_L; i++) {
    Cellule *p1 = NULL;

    for (int j = 0; j < M->Nb_C; j++) {
      int v;
      fichier >> v;

      Cellule *nv = new Cellule;
      nv->Info = v;
      nv->Ind_L = i;
      nv->Ind_C = j;
      nv->Suiv_C = NULL;

      if (M->TV[i] == NULL) {
        M->TV[i] = nv;
      } else {
        p1->Suiv_C = nv;
      }
      p1 = nv;
    }
  }

  fichier.close();
  std::cout << "Matrix has been created from the file : " << Name << std::endl;
}

void Afficher_Mat(PMat M) {
  if (M != NULL) {
    std::cout << "----------- Display the Matrix -----------" << std::endl;
    for (int i = 0; i < M->Nb_L; i++) {
      Cellule *p2 = M->TV[i];
      while (p2 != NULL) {
        std::cout << p2->Info << " ";
        p2 = p2->Suiv_C;
      }
      std::cout << std::endl;
    }
  }
}

void Liberer_Mat(PMat &M) {
  if (M != NULL) {
    for (int i = 0; i < M->Nb_L; i++) {
      Cellule *p3 = M->TV[i];

      while (p3 != NULL) {
        Cellule *psuiv = p3->Suiv_C;

        delete p3;

        p3 = psuiv;
      }
    }

    delete M;

    M = NULL;

    std::cout << "Matrix has been freed..." << std::endl;
  }
}

void SommeMat(PMat M1, PMat M2, PMat &M3) {
  if (M1 == NULL || M2 == NULL) {
    std::cout << "One of the matrices is NULL. Cannot perform addition."
              << std::endl;
    return;
  }

  if (M1->Nb_L != M2->Nb_L || M1->Nb_C != M2->Nb_C) {
    std::cout << "Matrices dimensions do not match." << std::endl;
    return;
  }

  Init_Mat(M3);
  M3->Nb_L = M1->Nb_L;
  M3->Nb_C = M1->Nb_C;

  for (int i = 0; i < M1->Nb_L; i++) {
    Cellule *q = M1->TV[i];
    Cellule *p = M2->TV[i];
    Cellule *prev = NULL;

    while (q != NULL || p != NULL) {
      int sum = 0;
      int row = (q != NULL) ? q->Ind_L : p->Ind_L;
      int col = (q != NULL) ? q->Ind_C : p->Ind_C;

      if (p == NULL || (q != NULL && q->Ind_C < p->Ind_C)) {
        sum = q->Info;
        q = q->Suiv_C;
      } else if (q == NULL || (p != NULL && p->Ind_C < q->Ind_C)) {
        sum = p->Info;
        p = p->Suiv_C;
      } else {
        sum = q->Info + p->Info;
        q = q->Suiv_C;
        p = p->Suiv_C;
      }

      if (sum != 0) {
        Cellule *newCell = new Cellule;
        newCell->Info = sum;
        newCell->Ind_L = row;
        newCell->Ind_C = col;
        newCell->Suiv_C = NULL;

        if (M3->TV[i] == NULL) {
          M3->TV[i] = newCell;
        } else {
          prev->Suiv_C = newCell;
        }
        prev = newCell;
      } else {
        Cellule *newCell = new Cellule;
        newCell->Info = 0;
        newCell->Ind_L = row;
        newCell->Ind_C = col;
        newCell->Suiv_C = NULL;

        if (M3->TV[i] == NULL) {
          M3->TV[i] = newCell;
        } else {
          prev->Suiv_C = newCell;
        }
        prev = newCell;
      }
    }
  }
  std::cout << "Sum of matrices computed." << std::endl;
}

void Produit(PMat M1, PMat M2, PMat &M4) {
  if (M1 == NULL || M2 == NULL) {
    std::cout << "One of the matrices is NULL. Cannot perform multiplication."
              << std::endl;
    return;
  }

  if (M1->Nb_C != M2->Nb_L) {
    std::cout << "Matrices dimensions do not match for multiplication."
              << std::endl;
    return;
  }

  Init_Mat(M4);
  M4->Nb_L = M1->Nb_L;
  M4->Nb_C = M2->Nb_C;

  for (int i = 0; i < M1->Nb_L; i++) {
    for (int j = 0; j < M2->Nb_C; j++) {
      int sum = 0;
      Cellule *p1 = M1->TV[i];
      while (p1 != NULL) {
        Cellule *p2 = M2->TV[p1->Ind_C];
        while (p2 != NULL && p2->Ind_C != j) {
          p2 = p2->Suiv_C;
        }
        if (p2 != NULL) {
          sum += p1->Info * p2->Info;
        }
        p1 = p1->Suiv_C;
      }
      if (sum != 0) {
        Cellule *newCell = new Cellule;
        newCell->Info = sum;
        newCell->Ind_L = i;
        newCell->Ind_C = j;
        newCell->Suiv_C = NULL;

        if (M4->TV[i] == NULL) {
          M4->TV[i] = newCell;
        } else {
          Cellule *temp = M4->TV[i];
          while (temp->Suiv_C != NULL) {
            temp = temp->Suiv_C;
          }
          temp->Suiv_C = newCell;
        }
      } else {
        Cellule *newCell = new Cellule;
        newCell->Info = 0;
        newCell->Ind_L = i;
        newCell->Ind_C = j;
        newCell->Suiv_C = NULL;

        if (M4->TV[i] == NULL) {
          M4->TV[i] = newCell;
        } else {
          Cellule *temp = M4->TV[i];
          while (temp->Suiv_C != NULL) {
            temp = temp->Suiv_C;
          }
          temp->Suiv_C = newCell;
        }
      }
    }
  }
  std::cout << "Product of matrices computed." << std::endl;
}

void Puissance(PMat M, int K, PMat &Res) {
  if (M == NULL || K < 1) {
    std::cout << "Matrix is NULL or power is less than 1." << std::endl;
    return;
  }

  PMat Temp;
  Init_Mat(Res);
  Init_Mat(Temp);
  Res = M; // Start with the matrix itself for the first power.

  for (int i = 1; i < K; i++) {
    Produit(Res, M, Temp);
    Liberer_Mat(Res);
    Res = Temp;
    Init_Mat(Temp);
  }
  Liberer_Mat(Temp);
  std::cout << "Matrix raised to power " << K << " computed." << std::endl;
}

void Sigma_Puissance(PMat M, int n, PMat &S) {
  if (M == NULL || n < 1) {
    std::cout << "Matrix is NULL or n is less than 1." << std::endl;
    return;
  }

  PMat Temp;
  Init_Mat(S);

  for (int i = 1; i <= n; i++) {
    Puissance(M, i, Temp);
    PMat SumTemp;
    SommeMat(S, Temp, SumTemp);
    Liberer_Mat(S);
    S = SumTemp;
    Liberer_Mat(Temp);
  }
  std::cout << "Sum of powers up to " << n << " computed." << std::endl;
}
