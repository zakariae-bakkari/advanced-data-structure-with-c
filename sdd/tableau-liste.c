#include <stdio.h>
#include <stdlib.h>

// === Main ===
int main()
{
   TList *liste = create_tab();
   init_ttab(liste);
   printf("\n\n========== Test des fonctions du liste (tableau) ==========\n\n");
   // tester l'allocation memoire a partir de la fonction create_tab
   if (!liste)
   {
      printf("Tableau initialisee avec succes.\n\n");
   }

   // tester la fonction taille
   printf("1. Taille initiale du tableau: %d\n\n", nombre_elements_ttab(*liste));

   // tester la fonction insertion
   printf("2. Insertion de 8 elements dans le tableau:\n");
   insert_fin_ttab(liste, 5);
   insert_fin_ttab(liste, 10);
   insert_fin_ttab(liste, 15);
   insert_fin_ttab(liste, 34);
   insert_fin_ttab(liste, 15);
   insert_fin_ttab(liste, 34);
   insert_fin_ttab(liste, 15);
   insert_fin_ttab(liste, 34);

   printf("Taille du tableau apres insertion: %d\n", nombre_elements_ttab(*liste));
   printf("\n3. Afficher le tableau apres l'insertion:\n");
   afficher_ttab(*liste);

   // tester la fonction rechercher
   int valeur_recherchee = 10; // Exemple de valeur à rechercher
   int indice_trouve = recherche_ttab(*liste, valeur_recherchee);
   printf("\n\n4. Recherche de la valeur %d dans le tableau:\n", valeur_recherchee);
   if (indice_trouve != -1)
      printf("Valeur %d trouvee a l'indice %d dans le tableau.\n", valeur_recherchee, indice_trouve);
   else
      printf("Valeur %d non trouvee dans le tableau.\n", valeur_recherchee);

   // tester la fonciton supprimer
   int indice_a_supprimer = 1; // Exemple d'indice à supprimer
   supprimer_ttab(liste, indice_a_supprimer);
   printf("\n5. Afficher le tableau apres la suppression a l'indice %d:\n", indice_a_supprimer);
   afficher_ttab(*liste);

   // tester la fonction modifier
   int indice_a_modifier = 0; // Exemple d'indice à modifier
   int nouvelle_valeur = 99;  // Nouvelle valeur à insérer
   modifier_ttab(liste, indice_a_modifier, nouvelle_valeur);
   printf("\n\n6. Afficher le tableau apres la modification a l'indice %d:\n", indice_a_modifier);
   afficher_ttab(*liste);

   // supprimer le premier occurence d'une valeur
   int valeur_a_supprimer = 15; // Exemple de valeur à supprimer
   supprimer_premier_occ_ttab(liste, valeur_a_supprimer);
   printf("\n\n7. Afficher le tableau apres la suppression du premier occurence de la valeur %d:\n", valeur_a_supprimer);
   afficher_ttab(*liste);

   // supprimer tout les occurences d'une valeur
   printf("\n\n8. Supprimer tout les occurences de la valeur %d:\n", valeur_a_supprimer);
   int nb_supprimees = supprimer_tout_occurences_ttab(liste, valeur_a_supprimer);
   if (nb_supprimees >= 0)
      printf("Nombre d'occurrences supprimees: %d\n", nb_supprimees);
   else
      errors_message_ttab(nb_supprimees);
   printf("\nAfficher le tableau apres la suppression de tout les occurences de la valeur %d:\n", valeur_a_supprimer);
   afficher_ttab(*liste);

   // modifier le premier occurence d'une valeur
   int ancienne_valeur = 34;       // Exemple de valeur à modifier
   int nouvelle_valeur_modif = 77; // Nouvelle valeur à insérer
   modifier_premier_occ_ttab(liste, ancienne_valeur, nouvelle_valeur_modif);
   printf("\n\n9. Afficher le tableau apres la modification du premier occurence de la valeur %d:\n", ancienne_valeur);
   afficher_ttab(*liste);

   // modifier tout les occurences d'une valeur
   modifier_tout_occurences_ttab(liste, ancienne_valeur, nouvelle_valeur_modif);
   printf("\n\n10. Afficher le tableau apres la modification de tout les occurences de la valeur %d:\n", nouvelle_valeur_modif);
   afficher_ttab(*liste);
   // Libérer la mémoire allouée pour le tableau
   free(liste);

   printf("\n\n========== Fin des tests ==========\n\n");
   return 0;
}