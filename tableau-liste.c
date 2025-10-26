#include <stdio.h>
#include <stdlib.h>
#define TAILLE 10

// structure du tableau avec son indice du dernier element en definition leur type
typedef struct TList
{
   int tab[TAILLE];
   int indice_dr;
} TList;

// fonction de creation du tableau dynamique "allocation dynamique"
TList *create_tab()
{
   TList *liste = (TList *)malloc(sizeof(TList));
   if (!liste)
      exit(-1); // Erreur d'allocation mémoire
   return ((TList *)liste);
}

// inisialiser l'indice du dernier element du tableau a -1 pour indiquer qu'il est vide au debut
int init_ttab(TList *liste)
{
   if (!liste)
      return ((int)-1);   // Erreur : le tableau n'existe pas (utilisant un pointeur NULL)
   liste->indice_dr = -1; //? Initialiser l'indice du dernier élément
   return ((int)0);       // Succès
}

// fonction pour tester si un tableau est vide ou pas
int est_vide_ttab(TList liste)
{
   return ((int)(liste.indice_dr == -1)); // Retourne 1(true) si le tableau est vide, sinon 0 (false)
}

// fonction pour obtenir le nombre d'elements dans le tableau
int nombre_elements_ttab(TList liste)
{
   return ((int)(liste.indice_dr + 1)); // Retourne le nombre d'éléments dans le tableau
}

// fonction d'insertion d'une valeur a un indice specifique dans le tableau
int insertion(TList *liste, int indice, int valeur)
{
   int ind; // Indice de parcours
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   if (est_vide_ttab(*liste))
      return ((int)-2); // Erreur : le tableau est vide
   if ((indice < 0) || (indice > liste->indice_dr + 1))
      return ((int)-3); // Erreur : indice invalide
   if (liste->indice_dr >= TAILLE - 1)
      return ((int)-4); // Erreur : le tableau est sature

   // Décaler les éléments vers la droite
   for (ind = liste->indice_dr; ind >= indice; liste->tab[ind + 1] = liste->tab[ind], ind--)
      ;
   liste->tab[indice] = valeur;
   liste->indice_dr++;
   return ((int)0); // Succès
}

// fonction de suppression d'une valeur  par l'indice specifique dans le tableau
int supprimer_ttab(TList *liste, int indice)
{
   int ind; // Indice de parcours
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   if (est_vide_ttab(*liste))
      return ((int)-2); // Erreur : le tableau est vide
   if ((indice < 0) || (indice > liste->indice_dr))
      return ((int)-3); // Erreur : indice invalide

   // decaler les elements a gauche
   for (ind = indice; ind < liste->indice_dr; ind++)
      liste->tab[ind] = liste->tab[ind + 1];
   liste->indice_dr--; // Decrementer l'indice du dernier élément
   return ((int)0);    // Succès
}

// fonction de suppression de la premiere occurence d'une valeur dans le tableau
int supprimer_premier_occ_ttab(TList *liste, int valeur)
{
   int ind, indice_trouve = -1;
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   if (est_vide_ttab(*liste))
      return ((int)-2); // Erreur : le tableau est vide

   // Rechercher la première occurrence de la valeur
   for (ind = 0; ind <= liste->indice_dr; ind++)
   {
      if (liste->tab[ind] == valeur)
      {
         indice_trouve = ind;
         break;
      }
   }

   if (indice_trouve == -1)
      return ((int)-3); // Erreur : valeur non trouvée

   // Supprimer l'élément à l'indice trouvé
   for (ind = indice_trouve; ind < liste->indice_dr; ind++)
      liste->tab[ind] = liste->tab[ind + 1];
   liste->indice_dr--; // Decrementer l'indice du dernier élément
   return ((int)0);    // Succès
}

// fonction de suppression de toutes les occurences d'une valeur dans le tableau
int supprimer_tout_occurences_ttab(TList *liste, int valeur)
{
   int ind, count = 0;
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   if (est_vide_ttab(*liste))
      return ((int)-2); // Erreur : le tableau est vide

   ind = 0;
   while (ind <= liste->indice_dr)
   {
      if (liste->tab[ind] == valeur)
      {
         // Supprimer l'élément à l'indice trouvé
         for (int j = ind; j < liste->indice_dr; j++)
            liste->tab[j] = liste->tab[j + 1];
         liste->indice_dr--; // Decrementer l'indice du dernier élément
         count++;
      }
      else
      {
         ind++;
      }
   }

   if (count == 0)
      return ((int)-3); // Erreur : valeur non trouvée

   return ((int)count); // Retourne le nombre d'occurrences supprimées
}

// fonction de recherche d'une valeur dans le tableau
int recherche_ttab(TList liste, int valeur)
{
   int ind;
   for (ind = 0; ind <= liste.indice_dr; ind++)
      if (liste.tab[ind] == valeur)
         return ((int)ind); // Succès : valeur trouvée, retourne l'indice
   return ((int)-1);        // Erreur : valeur non trouvée
}

// fonction d'insertion d'une valeur a la fin du tableau
int insert_fin_ttab(TList *liste, int valeur)
{
   // Vérifier si le tableau est existant
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   // Vérifier si le tableau est sature
   if (liste->indice_dr == TAILLE - 1)
      return ((int)-2); // Erreur : le tableau est sature

   liste->indice_dr++;
   liste->tab[liste->indice_dr] = valeur;
   return (0); // Succès
}

// fonction de remplissage du tableau interactivement avec l'utilisateur
int remplir_ttab(TList *liste)
{
   int valeur, resultas;
   char c;
   if (!liste)          //   Verifier si le tableau est existant
      return ((int)-1); // Erreur : le tableau n'existe pas

   printf("\n===== REMPLISSAGE DU TABLEAU =====\n");

   do
   {
      printf("Entrez l'element %d/%d: ", liste->indice_dr + 2, TAILLE);
      scanf("%d", &valeur);
      resultas = insert_fin_ttab(liste, valeur);

      if (resultas == 0)
         printf(" -> Element %d ajoute avec succes a l'indice %d\n", valeur, liste->indice_dr);

      if (liste->indice_dr < TAILLE - 1) // Verifier si le tableau est completement rempli
      {
         printf("\nContinuer le remplissage ? (o/n): ");
         scanf(" %c", &c);
      }
      else
      {
         printf("\nTableau completement rempli!\n");
         break;
      }
      printf("\n--------------------------------\n");
   } while (((c != 'n') && (c != 'N')));

   printf("\n===== FIN DU REMPLISSAGE =====\n");
   return ((int)0); // Succès
}

// fonction d'affichage du tableau
void afficher_ttab(TList liste)
{
   int ind;

   for (ind = 0; ind < TAILLE; ind++)
      if (ind > liste.indice_dr)
         printf("| ");
      else
         printf("|%d",liste.tab[ind]);
}

// fonction de modification d'une valeur a un indice specifique dans le tableau
int modifier_ttab(TList *liste, int indice, int valeur)
{
   int ind;
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   if (est_vide_ttab(*liste))
      return ((int)-2); // Erreur : le tableau est vide
   if ((indice < 0) || (indice > liste->indice_dr))
      return ((int)-3); // Erreur : indice invalide
   liste->tab[indice] = valeur;
   return ((int)0); // Succès
}

// fonction de modification de la premier occurence d'une valeur dans le tableau
int modifier_premier_occ_ttab(TList *liste, int ancienne_valeur, int nouvelle_valeur)
{
   int ind, indice_trouve = -1;
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   if (est_vide_ttab(*liste))
      return ((int)-2); // Erreur : le tableau est vide

   // Rechercher la première occurrence de l'ancienne valeur
   for (ind = 0; ind <= liste->indice_dr; ind++)
   {
      if (liste->tab[ind] == ancienne_valeur)
      {
         indice_trouve = ind;
         break;
      }
   }

   if (indice_trouve == -1)
      return ((int)-3); // Erreur : valeur non trouvée

   // Modifier l'élément à l'indice trouvé
   liste->tab[indice_trouve] = nouvelle_valeur;
   return ((int)0); // Succès
}

// focntion de modification de toutes les occurences d'une valeur dans le tableau
int modifier_tout_occurences_ttab(TList *liste, int ancienne_valeur, int nouvelle_valeur)
{
   int ind, count = 0;
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   if (est_vide_ttab(*liste))
      return ((int)-2); // Erreur : le tableau est vide

   // Parcourir le tableau pour modifier toutes les occurrences
   for (ind = 0; ind <= liste->indice_dr; ind++)
   {
      if (liste->tab[ind] == ancienne_valeur)
      {
         liste->tab[ind] = nouvelle_valeur;
         count++;
      }
   }

   if (count == 0)
      return ((int)-3); // Erreur : valeur non trouvée

   return ((int)count); // Retourne le nombre d'occurrences modifiées
}

// ====== Menu pour les fonctions  ======
int menu()
{
   printf("\n===== MENU =====\n");
   printf("1. Remplir le tableau\n");
   printf("2. Afficher le tableau\n");
   printf("3. Rechercher une valeur dans le tableau\n");
   printf("4. Inserer une valeur dans le tableau\n");
   printf("5. Supprimer une valeur dans le tableau\n");
   printf("6. Modifier une valeur dans le tableau\n");
   printf("7. Nombre d'elements dans le tableau\n");
   printf("8. Quitter\n");
   printf("================\n");
   int choix;
   // en demande d'ecrire jusqu'au le nombre choisir est compris entre 1 et 8 (inclus 1 et 8)
   do
   {
      printf("Entrez votre choix: ");
      scanf("%d", &choix);
   } while (choix < 1 || choix > 8);
   return choix;
}

// === fonction des messages d'errors ===
void errors_message_ttab(int nombre)
{
   switch (nombre)
   {
   case -1:
      printf("Le tableau n'existe pas.\n");
      break;
   case -2:
      printf("Le tableau est vide.\n");
      break;
   case -3:
      printf("Indice invalide.\n");
      break;
   case -4:
      printf("Le tableau est sature.\n");
      break;

   default:
      printf("problem inconue\n");
      break;
   }
}
// === Main ===
int main()
{
   TList *liste = create_tab();
   init_ttab(liste);
   printf("\n\n========== Test des fonctions du tableau ==========\n\n");
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