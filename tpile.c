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
      return ((int)-1); // errer d'allocation
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
   if (est_sature_tpile(*mapile))
      return ((int)-3);
   (mapile->sommet)--;
   return ((int)1);
}

void afficher_tpile(Pile mapile)
{
   if (!est_vide_tpile(mapile))
   {
      printf("\nsommet indice = %d \n", mapile.sommet);
      while (mapile.sommet >= 0)
      {
         printf("pile[%d]=%d ", mapile.sommet, mapile.tableau[mapile.sommet]);
         depiler_tpile(&mapile);         
      }
   }
   else
   {
      printf("\nvide");
   }
}

int main()
{
   Pile *pile = create_tpile();
   init_tpile(pile);
   empiler_tpile(pile, 10);
   empiler_tpile(pile, 15);
   empiler_tpile(pile, 20);
   afficher_tpile(*pile);
   depiler_tpile(pile);
   printf("\n---------------apres depiler-----------");
   afficher_tpile(*pile);
}
