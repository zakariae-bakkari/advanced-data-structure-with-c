#include <stdio.h>
#include <stdlib.h>
#define maxelem 10

typedef struct Pile
{
   int tableau[maxelem];
   int sommet;
} Pile;

Pile *create_tpile()
{
   Pile *maPile = (Pile *)malloc(sizeof(Pile));
   if (!maPile)
   {
      printf("Erreur de mémoire !\n");
      exit(0);
   }
   return maPile;
}

int init_tpile(Pile *maPile)
{
   // tester l'existance
   if (!maPile)
      return ((int)-1);
   maPile->sommet = -1; // initialiser le sommet a -1
   return 1;
}

int est_vide_tpile(Pile maPile)
{
   return ((int)maPile.sommet == -1);
}

// test de saturatoin
int est_sature_tpile(Pile mapile)
{
   return ((int)(mapile.sommet) == (maxelem - 1));
}

// empiler
int empiler_tpile(Pile *mapile, int valeur)
{
   // tester l'existance
   if (!mapile)
      return ((int)-1);
   // tester saturation
   if (est_sature_tpile(*mapile))
      return ((int)-2);

   mapile->tableau[++(mapile->sommet)] = valeur;
   return ((int)1);
}

// depiler
int depiler_tpile(Pile *mapile)
{
   // tester l'existance
   if (!mapile)
      return ((int)-1);
   // tester si il est vide
   if (est_vide_tpile(*mapile))
      return ((int)-3);
   (mapile->sommet)--;
   return ((int)1);
}

// ...existing code...
void afficher_tpile(Pile *mapile)
{
   if (!mapile || est_vide_tpile(*mapile))
   {
      printf("Pile vide\n");
      return;
   }
   
   // Sauvegarder les valeurs dans un tableau temporaire
   int temp[maxelem];
   int nb_elements = 0;
   
   printf("Affichage LIFO: ");
   
   // Phase 1: Dépiler et sauvegarder
   while (!est_vide_tpile(*mapile))
   {
      temp[nb_elements] = mapile->tableau[mapile->sommet];
      printf("pile[%d]=%d ", mapile->sommet, temp[nb_elements]);
      depiler_tpile(mapile);
      nb_elements++;
   }
   
   // Phase 2: Restaurer la pile
   for (int i = nb_elements - 1; i >= 0; i--)
   {
      empiler_tpile(mapile, temp[i]);
   }
   
   printf("\n");
}

int main()
{
   Pile *pile = create_tpile();
   int etat = init_tpile(pile);
   printf("\n\n========== Test des fonctions de la pile (tableau) ==========\n\n");
   if (etat == -1)
   {
      printf("Erreur d'allocation memoire\n");
      return -1;
   }
   else
      printf("La pile est cree avec success\n");
   printf("\n1. tester si la pile est vide : ");
   if (est_vide_tpile(*pile))
      printf("la pile est vide\n");
   else
      printf("la pile n'est pas vide\n");
   printf("\n2. empiler des elements dans la pile:\n");
   empiler_tpile(pile, 5);
   empiler_tpile(pile, 10);
   empiler_tpile(pile, 15);
   printf("la taille de la pile apres empiler 3 elements est : %d\n", pile->sommet + 1);
   printf("\n3. afficher la pile:\n");
   afficher_tpile(pile);
   printf("\n");

   // depiler un element
   printf("\n4. depiler un element de la pile:\n");
   depiler_tpile(pile);
   printf("la taille de la pile apres depiler un element est : %d\n", pile->sommet + 1);
   printf("afficher la pile apres depiler un element:\n");
   afficher_tpile(pile);

   // test de saturation
   if (est_sature_tpile(*pile))
      printf("\nla pile est sature\n");
   else
      printf("\nla pile n'est pas sature\n");
   printf("\n5. empiler des elements jusqu'a saturer la pile:\n");
   if (est_sature_tpile(*pile))
   {
      printf("La pile est déjà saturée, impossible d'empiler davantage.\n");
   }
   else
   {
      for (int i = 0; i < 10; i++)
      {
         int res = empiler_tpile(pile, i * 10);
         if (res < 0)
         {
            printf("Erreur lors de l'empilage: %d\n", res);
            break;
         }
      }
   }
   printf("la taille de la pile apres empiler jusqu'a saturer est : %d\n", pile->sommet + 1);
   printf("afficher la pile apres saturation:\n");
   afficher_tpile(pile);
   printf("\n");
   printf("\n\n========== Fin des tests de la pile (tableau) ==========\n\n");
   return 0;
}
