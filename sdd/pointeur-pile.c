#include "header.h"
int main()
{
   Pile *maPile = init_pile();
   printf("\n\n========== Test des fonctions de la pile (pointeur) ==========\n\n");
   if (maPile == NULL)
   {
      printf("Pile initialisee avec succes.\n\n");
   }

   printf("1. Taille initiale de la pile: %d\n", taille_recursive_pile(maPile));

   printf("\n2. empiler des elements 5, 10, 15 dans la pile.\n");
   maPile = empiler_pile(maPile, 5);
   maPile = empiler_pile(maPile, 10);
   maPile = empiler_pile(maPile, 15);
   maPile = empiler_pile(maPile, 23);
   maPile = empiler_pile(maPile, 6);
   printf("Taille de la pile apres empilage: %d\n", taille_recursive_pile(maPile));
   printf("Contenu de la pile: ");
   afficher_pile(maPile);

   printf("\n3. depiler un element de la pile.\n");
   maPile = depiler_pile(maPile);
   printf("Taille de la pile apres depilage: %d\n", taille_recursive_pile(maPile));
   printf("Contenu de la pile: ");
   afficher_pile(maPile);
   printf("\n4. recherche d'une valeur dans la pile.\n");
   int valeur_recherchee = 23;
   int position_trouvee = recherche_recursive_pile(maPile, valeur_recherchee);
   if (position_trouvee != 0)
      printf("Valeur %d trouvee a la position %d dans la pile.\n", valeur_recherchee, position_trouvee);
   else
      printf("Valeur %d non trouvee dans la pile.\n", valeur_recherchee);
   afficher_pile(maPile);

   free(maPile);
   // tester la fonction inserer_bonne_place_pile
   printf("\n5. inserer des elements dans la pile en ordre croissant.\n");
   Pile *pile_ordonnee = init_pile();
   pile_ordonnee = inserer_bonne_place_pile(pile_ordonnee, 30);
   pile_ordonnee = inserer_bonne_place_pile(pile_ordonnee, 10);
   pile_ordonnee = inserer_bonne_place_pile(pile_ordonnee, 20);
   pile_ordonnee = inserer_bonne_place_pile(pile_ordonnee, 40);
   pile_ordonnee = inserer_bonne_place_pile(pile_ordonnee, 25);
   printf("Contenu de la pile ordonnee: ");
   afficher_pile(pile_ordonnee);

   // tester la fonction minimum_pile
   printf("\n6. trouver le minimum dans la pile.\n");
   printf("Minimum dans la pile: %d\n", minimum_pile(pile_ordonnee));

   // tester la fonction trier_pile
   printf("\n7. trier la pile.\n");
   Pile *pile_a_trier = init_pile();
   pile_a_trier = empiler_pile(pile_a_trier, 50);
   pile_a_trier = empiler_pile(pile_a_trier, 10);
   pile_a_trier = empiler_pile(pile_a_trier, 30);
   pile_a_trier = empiler_pile(pile_a_trier, 20);
   pile_a_trier = empiler_pile(pile_a_trier, 40);
   printf("Contenu de la pile avant tri: ");
   afficher_pile(pile_a_trier);
   pile_a_trier = trier_pile(pile_a_trier);
   printf("Contenu de la pile apres tri: ");
   afficher_pile(pile_a_trier);

   printf("\n\n========== fin du testes ==========\n");
   return 0;
}

// int main()
// {
//    Pile *maPile = init_pile();
//    maPile = empiler_pile(maPile, 1);
//    maPile = empiler_pile(maPile, 3);
//    test(maPile);
//    afficher_pile(maPile);
//    maPile = test2(maPile);
//    afficher_pile(maPile);
// }