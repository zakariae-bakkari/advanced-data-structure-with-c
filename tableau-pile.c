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

   printf("\n=== DEMONSTRATION DE LA PILE mise en oeuvre avec tableau ===\n");

   if (init_tpile(pile) == 1)
      printf("\n1. Pile initialisee avec succes");

   // Verification pile vide
   if (est_vide_tpile(*pile))
      printf("\n2. La pile est vide");
   else
      printf("\n   La pile n'est pas vide");

   // Empilement des valeurs
   printf("\n\n3. Empilement des valeurs");
   printf("\n   Empiler 10: %s", empiler_tpile(pile, 10) == 1 ? "Succes" : "Echec");
   printf("\n   Empiler 15: %s", empiler_tpile(pile, 15) == 1 ? "Succes" : "Echec");
   printf("\n   Empiler 20: %s", empiler_tpile(pile, 20) == 1 ? "Succes" : "Echec");

   // Affichage de la pile
   printf("\n\n4. Affichage de la pile apres empilement:");
   afficher_tpile(*pile);

   // Verification pile non vide
   printf("\n\n5. Test pile vide");
   if (est_vide_tpile(*pile))
      printf("\n   La pile est vide");
   else
      printf("\n   La pile n'est pas vide");

   // Verification pile saturee
   printf("\n\n6. Test pile saturee");
   if (est_sature_tpile(*pile))
      printf("\n   La pile est saturee");
   else
      printf("\n   La pile n'est pas saturee");

   // Depilement
   printf("\n\n7. Depilement d'une valeur");
   if (depiler_tpile(pile) == 1)
      printf("\n   Depilement reussi");

   // Affichage apres depilement
   printf("\n\n8. Affichage de la pile apres depilement:");
   afficher_tpile(*pile);

   // Empilement jusqu'à saturation
   printf("\n\n9. Empilement jusqu'a saturation");
   for (int i = 30; i < 100; i += 10)
   {
      int result = empiler_tpile(pile, i);
      printf("\n   Empiler %d: %s", i, result == 1 ? "Succes" : (result == -2 ? "Echec (pile saturee)" : "Echec"));
      if (result == -2)
         break;
   }
   
   // Affichage de la pile saturée
   printf("\n\n10. Affichage de la pile saturee:");
   afficher_tpile(*pile);

   // Libération de la mémoire
   free(pile);
   printf("\n\n=== FIN DE LA DEMONSTRATION ===\n");

   return 0;
}
