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
   if (est_sature_tpile(*mapile))
      return ((int)-3);
   (mapile->sommet)--;
   return ((int)1);
}

void afficher_tpile(Pile mapile)
{
   if (!est_vide_tpile(mapile))
   {
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
   printf("la pile est initialiser\n");
   printf("\n1. tester si la pile est vide : ");
   if (est_vide_tpile(*pile))
      printf("la pile est vide\n");
   else
      printf("la pile n'est pas vide\n");
   printf("\n2. empiler des elements dans la pile:\n");
   empiler_tpile(pile, 5);
   empiler_tpile(pile, 10);
   empiler_tpile(pile, 15);
   printf("la taille de la pile apres empiler 3 elements est : %d\n",pile->sommet + 1);
   printf("\n3. afficher la pile:\n");
   afficher_tpile(*pile);
   printf("\n");

   // depiler un element
   printf("\n4. depiler un element de la pile:\n");
   depiler_tpile(pile);
   printf("la taille de la pile apres depiler un element est : %d\n",pile->sommet + 1);
   printf("afficher la pile apres depiler un element:\n");
   afficher_tpile(*pile);

   //test de saturation
   if (est_sature_tpile(*pile))
      printf("\nla pile est sature\n");
   else
      printf("\nla pile n'est pas sature\n");   
   
   return 0;
}
