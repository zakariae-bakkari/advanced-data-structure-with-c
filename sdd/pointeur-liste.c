#include "header.h"

int main()
{
   // Creer une liste vide
   liste *maliste = init_null();
   printf("\n\n========== Test des fonctions de la liste chaine (pointeur) ==========\n\n");
   if (!maliste)
   {
      printf("La liste est initialisee a NULL.\n");
   }

   // Test insertion
   printf("\n1. Test d'insertion par position:\n");
   maliste = inserer_liste(maliste, 10, 1);
   maliste = inserer_liste(maliste, 20, 1);
   maliste = inserer_liste(maliste, 40, 1);
   maliste = inserer_liste(maliste, 25, 1);
   maliste = inserer_liste(maliste, 40, 1);
   maliste = inserer_liste(maliste, 30, 1);
   maliste = inserer_liste(maliste, 40, 1);

   printf("afficher la liste apres insertions: ");
   afficher_liste(maliste);

   // la taille
   printf("\n2. Taille de la liste apres insertions: %d\n", taille_liste_recursive(maliste));
   // Test modification
   printf("\n3. Test de modification par position:\n");
   printf("modifier la position 2 avec la valeur 25\n");
   maliste = modifier_liste(maliste, 2, 25);
   printf("Apres modification: ");
   afficher_liste(maliste);

   // Test suppression par position
   printf("\n4. Test de suppression par position:\n");
   printf("supprimer la position 1\n");
   maliste = supprimer(maliste, 1);
   printf("Apres suppression: ");
   afficher_liste(maliste);

   // Test suppression par valeur
   printf("\n5. Test de suppression par valeur (25):\n");
   maliste = supprimer_prem_occu(maliste, 25);
   printf("Apres suppression premiere occurrence de 25: ");
   afficher_liste(maliste);

   // Test suppression toutes occurrences
   printf("\n6. Test de suppression de toutes les occurrences(40):\n");
   maliste = supprimer_tout_occu(maliste, 40);
   printf("Apres suppression de tous les 40: ");
   afficher_liste(maliste);

   // Afficher la taille
   printf("\n6. Taille de la liste: %d\n", taille_liste_recursive(maliste));

   // Liberer la memoire
   printf("\nNettoyage de la liste...\n");
   while (!est_vide_liste(maliste))
   {
      maliste = supprimer(maliste, 1);
   }
   printf("Liste finale: ");
   afficher_liste(maliste);
   // tester la fonction inserer_bonne_place_pliste
   printf("\n7. Test d'insertion en ordre croissant:\n");
   maliste = inserer_bonne_place_pliste(maliste, 50);
   maliste = inserer_bonne_place_pliste(maliste, 20);
   maliste = inserer_bonne_place_pliste(maliste, 30);
   maliste = inserer_bonne_place_pliste(maliste, 10);
   maliste = inserer_bonne_place_pliste(maliste, 40);
   printf("Apres insertions en ordre croissant: ");
   afficher_liste(maliste);
   // tester l'insertion par cellule
   printf("\n7.b Test d'insertion en ordre croissant par cellule:\n");
   cellule *cel = createcellule(25);
   maliste = inserer_bonne_place_pliste_par_cellule(maliste, cel);
   printf("Apres insertion de 25 par cellule en ordre croissant: ");
   afficher_liste(maliste);

   // tester la fonction trier_pliste
   printf("\n8. Test de tri de la liste:\n");
   liste *unsorted_list = init_null();
   unsorted_list = inserer_liste(unsorted_list, 30, 1);
   unsorted_list = inserer_liste(unsorted_list, 10, 1);
   unsorted_list = inserer_liste(unsorted_list, 50, 1);
   unsorted_list = inserer_liste(unsorted_list, 20, 1);
   unsorted_list = inserer_liste(unsorted_list, 40, 1);
   printf("Liste non triee: ");
   afficher_liste(unsorted_list);
   liste *sorted_list = trier_pliste(unsorted_list);
   printf("Liste triee: ");
   afficher_liste(sorted_list);

   // tester la fonction concatener_listes
   printf("\n9. Test de concatenation de deux listes:\n");
   liste *l1 = init_null();
   liste *l2 = init_null();
   l1 = inserer_liste(l1, 10, 1);
   l1 = inserer_liste(l1, 30, 1);
   l1 = inserer_liste(l1, 50, 1);
   // tester concatener l1 et l2 tel que l2 est vide
   printf("Concatenation de l1 et l2 (l2 vide):\n");
   liste *concat1 = concatener_listes(l1, l2);
   afficher_liste(concat1);
   l1 = init_null();
   l1 = inserer_liste(l1, 10, 1);
   l1 = inserer_liste(l1, 30, 1);
   l1 = inserer_liste(l1, 50, 1);

   l2 = inserer_liste(l2, 20, 1);
   l2 = inserer_liste(l2, 40, 1);
   l2 = inserer_liste(l2, 60, 1);
   // tester concatener l1 et l2
   // afficher les deux
   printf("Liste l1: ");
   afficher_liste(l1);
   printf("Liste l2: ");
   afficher_liste(l2);
   printf("Concatenation de l1 et l2:\n");
   liste *concat2 = concatener_listes(l1, l2);
   afficher_liste(concat2);
   afficher_liste(l1); // verifier que l1 est intact
   afficher_liste(l2); // verifier que l2 est intact

   // tester la fonction saisie_valeur_pliste
   printf("\n10. Test de saisie de valeurs avec insertion en ordre croissant:\n");
   liste *saisie_list = init_null();
   saisie_list = saisie_valeur_pliste(saisie_list);
   printf("Liste apres saisie et insertion en ordre croissant: ");
   afficher_liste(saisie_list);

   return 0;
}