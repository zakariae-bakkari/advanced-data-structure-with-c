#include "header.h"




int main()
{
   Tpile *pile = create_tpile();
   int etat = init_tpile(pile);
   printf("\n\n========== Test des fonctions de la pile (tableau) ==========\n\n");

   // tester l'allocation memoire a partir de la fonction init_tpile
   if (etat == -1)
   {
      printf("Erreur d'allocation memoire\n");
      return -1;
   }
   else
      printf("La pile est cree avec success\n");

   // tester la fonction est_vide
   printf("\n1. tester si la pile est vide : ");
   if (est_vide_tpile(*pile))
      printf("la pile est vide\n");
   else
      printf("la pile n'est pas vide\n");

   // empiler des elements
   printf("\n2. empiler des elements dans la pile:(5,10,15)\n");
   empiler_tpile(pile, 5);
   empiler_tpile(pile, 10);
   empiler_tpile(pile, 15);

   // tester la taille de la pile
   printf("la taille de la pile apres empiler 3 elements est : %d\n", pile->sommet + 1);

   // afficher la pile
   printf("\n3. afficher la pile:\n");
   afficher_tpile(*pile);
   printf("\n");

   // depiler un element
   printf("\n4. depiler un element de la pile:\n\n");
   depiler_tpile(pile);

   // tester la taille de la pile apres depiler
   printf("la taille de la pile apres depiler un element est : %d\n", pile->sommet + 1);

   // afficher la pile apres depiler
   printf("\n5. afficher la pile apres depiler un element:\n\n");
   afficher_tpile(*pile);

   // test de saturation
   if (est_sature_tpile(*pile))
      printf("\nla pile est sature\n");
   else
      printf("\nla pile n'est pas sature\n");

   // empiler jusqu'a saturer
   printf("\n6. empiler des elements jusqu'a saturer la pile:\n");
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
            printf("la pile est remplie totalement avec %d elements.\n", pile->sommet + 1);
            break;
         }
      }
   }

   // tester si la pile est sature
   printf("\n7. tester si la pile est sature : ");
   if (est_sature_tpile(*pile))
      printf("la pile est sature\n");
   else
      printf("la pile n'est pas sature\n");

   // afficher la pile apres saturation
   printf("\nafficher la pile apres saturation:\n");
   afficher_tpile(*pile);
   printf("\n");

   printf("\n\n========== Fin des tests de la pile (tableau) ==========\n\n");
   return 0;
}
