#include <stdio.h>
#include <stdlib.h>
#define TAILLE 10

// structure du tableau avec son indice du dernier element en definition leur type
typedef struct Matab
{
   int tab[TAILLE];
   int indice_dr;
} Matab;

//* fonction de creation du tableau dynamique "allocation dynamique"
Matab *create_tab()
{
   Matab *latab = (Matab *)malloc(sizeof(Matab));
   if (!latab)
      exit(-1); //! Erreur d'allocation mémoire
   return ((Matab *)latab);
}

//* inisialiser l'indice du dernier element du tableau a -1 pour indiquer qu'il est vide au debut
int init_ttab(Matab *latab)
{
   if (!latab)
      return ((int)-1);   //! Erreur : le tableau n'existe pas (utilisant un pointeur NULL)
   latab->indice_dr = -1; //? Initialiser l'indice du dernier élément
   return ((int)0);       //* Succès
}

//* fonction pour tester si un tableau est vide ou pas
int est_vide_ttab(Matab latab)
{
   return ((int)(latab.indice_dr == -1)); // Retourne 1(true) si le tableau est vide, sinon 0 (false)
}

//* fonction pour obtenir le nombre d'elements dans le tableau
int nombre_elements_ttab(Matab latab)
{
   return ((int)(latab.indice_dr + 1)); // Retourne le nombre d'éléments dans le tableau
}

//* fonction d'insertion d'une valeur a un indice specifique dans le tableau
int insertion(Matab *latab, int indice, int valeur)
{
   int ind; // Indice de parcours
   if (!latab)
      return ((int)-1); //! Erreur : le tableau n'existe pas
   if (est_vide_ttab(*latab))
      return ((int)-2); //! Erreur : le tableau est vide
   if ((indice < 0) || (indice > latab->indice_dr + 1))
      return ((int)-3); //! Erreur : indice invalide
   if (latab->indice_dr >= TAILLE - 1)
      return ((int)-4); //! Erreur : le tableau est sature

   // Décaler les éléments vers la droite
   for (ind = latab->indice_dr; ind >= indice; latab->tab[ind + 1] = latab->tab[ind], ind--)
      ;
   latab->tab[indice] = valeur;
   latab->indice_dr++;
   return ((int)0); // Succès
}

//* fonction de suppression d'une valeur  par l'indice specifique dans le tableau
int supprimer_ttab(Matab *latab, int indice)
{
   int ind; // Indice de parcours
   if (!latab)
      return ((int)-1); //! Erreur : le tableau n'existe pas
   if (est_vide_ttab(*latab))
      return ((int)-2); //! Erreur : le tableau est vide
   if ((indice < 0) || (indice > latab->indice_dr))
      return ((int)-3); //! Erreur : indice invalide

   // decaler les elements a gauche
   for (ind = indice; ind < latab->indice_dr; ind++)
      latab->tab[ind] = latab->tab[ind + 1];
   latab->indice_dr--; // Decrementer l'indice du dernier élément
   return ((int)0);    // Succès
}

//* fonction de suppression de la premiere occurence d'une valeur dans le tableau
int supprimer_premier_occ_ttab(Matab *latab, int valeur)
{
   int ind, indice_trouve = -1;
   if (!latab)
      return ((int)-1); //! Erreur : le tableau n'existe pas
   if (est_vide_ttab(*latab))
      return ((int)-2); //! Erreur : le tableau est vide

   // Rechercher la première occurrence de la valeur
   for (ind = 0; ind <= latab->indice_dr; ind++)
   {
      if (latab->tab[ind] == valeur)
      {
         indice_trouve = ind;
         break;
      }
   }

   if (indice_trouve == -1)
      return ((int)-3); //! Erreur : valeur non trouvée

   // Supprimer l'élément à l'indice trouvé
   for (ind = indice_trouve; ind < latab->indice_dr; ind++)
      latab->tab[ind] = latab->tab[ind + 1];
   latab->indice_dr--; // Decrementer l'indice du dernier élément
   return ((int)0);    // Succès
}

//* fonction de suppression de toutes les occurences d'une valeur dans le tableau
int supprimer_tout_occurences_ttab(Matab *latab, int valeur)
{
   int ind, count = 0;
   if (!latab)
      return ((int)-1); //! Erreur : le tableau n'existe pas
   if (est_vide_ttab(*latab))
      return ((int)-2); //! Erreur : le tableau est vide

   ind = 0;
   while (ind <= latab->indice_dr)
   {
      if (latab->tab[ind] == valeur)
      {
         // Supprimer l'élément à l'indice trouvé
         for (int j = ind; j < latab->indice_dr; j++)
            latab->tab[j] = latab->tab[j + 1];
         latab->indice_dr--; // Decrementer l'indice du dernier élément
         count++;
      }
      else
      {
         ind++;
      }
   }

   if (count == 0)
      return ((int)-3); //! Erreur : valeur non trouvée

   return ((int)count); // Retourne le nombre d'occurrences supprimées
}

//* fonction de recherche d'une valeur dans le tableau
int recherche_ttab(Matab latab, int valeur)
{
   int ind;
   for (ind = 0; ind <= latab.indice_dr; ind++)
      if (latab.tab[ind] == valeur)
         return ((int)ind); //* Succès : valeur trouvée, retourne l'indice
   return ((int)-1);        //! Erreur : valeur non trouvée
}

//* fonction d'insertion d'une valeur a la fin du tableau
int insert_fin_ttab(Matab *latab, int valeur)
{
   // Vérifier si le tableau est existant
   if (!latab)
      return ((int)-1); //! Erreur : le tableau n'existe pas
   // Vérifier si le tableau est sature
   if (latab->indice_dr == TAILLE - 1)
      return ((int)-2); //! Erreur : le tableau est sature

   latab->indice_dr++;
   latab->tab[latab->indice_dr] = valeur;
   return (0); // Succès
}

//* fonction de remplissage du tableau interactivement avec l'utilisateur
int remplir_ttab(Matab *latab)
{
   int valeur, resultas;
   char c;
   if (!latab)          //   Verifier si le tableau est existant
      return ((int)-1); //! Erreur : le tableau n'existe pas

   printf("\n===== REMPLISSAGE DU TABLEAU =====\n");

   do
   {
      printf("Entrez l'element %d/%d: ", latab->indice_dr + 2, TAILLE);
      scanf("%d", &valeur);
      resultas = insert_fin_ttab(latab, valeur);

      if (resultas == 0)
         printf(" -> Element %d ajoute avec succes a l'indice %d\n", valeur, latab->indice_dr);

      if (latab->indice_dr < TAILLE - 1) // Verifier si le tableau est completement rempli
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
   return ((int)0); //* Succès
}

//* fonction d'affichage du tableau
void afficher_ttab(Matab latab)
{
   int ind;

   for (ind = 0; ind <= latab.indice_dr; ind++)
      printf("t[%d] = %d \n", ind, latab.tab[ind]);
}

//* fonction de modification d'une valeur a un indice specifique dans le tableau
int modifier_ttab(Matab *latab, int indice, int valeur)
{
   int ind;
   if (!latab)
      return ((int)-1); //! Erreur : le tableau n'existe pas
   if (est_vide_ttab(*latab))
      return ((int)-2); //! Erreur : le tableau est vide
   if ((indice < 0) || (indice > latab->indice_dr))
      return ((int)-3); //! Erreur : indice invalide
   latab->tab[indice] = valeur;
   return ((int)0); // Succès
}

//* fonction de modification de la premier occurence d'une valeur dans le tableau
int modifier_premier_occ_ttab(Matab *latab, int ancienne_valeur, int nouvelle_valeur)
{
   int ind, indice_trouve = -1;
   if (!latab)
      return ((int)-1); //! Erreur : le tableau n'existe pas
   if (est_vide_ttab(*latab))
      return ((int)-2); //! Erreur : le tableau est vide

   // Rechercher la première occurrence de l'ancienne valeur
   for (ind = 0; ind <= latab->indice_dr; ind++)
   {
      if (latab->tab[ind] == ancienne_valeur)
      {
         indice_trouve = ind;
         break;
      }
   }

   if (indice_trouve == -1)
      return ((int)-3); //! Erreur : valeur non trouvée

   // Modifier l'élément à l'indice trouvé
   latab->tab[indice_trouve] = nouvelle_valeur;
   return ((int)0);    // Succès
}

//* focntion de modification de toutes les occurences d'une valeur dans le tableau
int modifier_tout_occurences_ttab(Matab *latab, int ancienne_valeur, int nouvelle_valeur)
{
   int ind, count = 0;
   if (!latab)
      return ((int)-1); //! Erreur : le tableau n'existe pas
   if (est_vide_ttab(*latab))
      return ((int)-2); //! Erreur : le tableau est vide

   // Parcourir le tableau pour modifier toutes les occurrences
   for (ind = 0; ind <= latab->indice_dr; ind++)
   {
      if (latab->tab[ind] == ancienne_valeur)
      {
         latab->tab[ind] = nouvelle_valeur;
         count++;
      }
   }

   if (count == 0)
      return ((int)-3); //! Erreur : valeur non trouvée

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
   Matab *latab = create_tab();
   init_ttab(latab);
   if (latab == NULL)
   {
      printf("Tableau initialisee avec succes.\n");
   }

   // tester la fonction taille
   printf("1. Taille initiale du tableau: %d\n", nombre_elements_ttab(*latab));

   // tester la fonction insertion
   insert_fin_ttab(latab, 5);
   insert_fin_ttab(latab, 10);
   insert_fin_ttab(latab, 15);
   insert_fin_ttab(latab, 34);
   insert_fin_ttab(latab, 15);
   insert_fin_ttab(latab, 34);
   insert_fin_ttab(latab, 15);
   insert_fin_ttab(latab, 34);

   printf("Taille du tableau apres insertion: %d\n", nombre_elements_ttab(*latab));
   printf("\n2. Afficher le tableau apres l'insertion:\n");
   afficher_ttab(*latab);

   // tester la fonction rechercher
   int valeur_recherchee = 10; // Exemple de valeur à rechercher
   int indice_trouve = recherche_ttab(*latab, valeur_recherchee);
   printf("\n3. Recherche de la valeur %d dans le tableau:\n", valeur_recherchee);
   if (indice_trouve != -1)
      printf("\nValeur %d trouvee a l'indice %d dans le tableau.\n", valeur_recherchee, indice_trouve);
   else
      printf("\nValeur %d non trouvee dans le tableau.\n", valeur_recherchee);

   // tester la fonciton supprimer
   int indice_a_supprimer = 1; // Exemple d'indice à supprimer
   supprimer_ttab(latab, indice_a_supprimer);
   printf("\n4. Afficher le tableau apres la suppression a l'indice %d:\n", indice_a_supprimer);
   afficher_ttab(*latab);

   // tester la fonction modifier
   int indice_a_modifier = 0; // Exemple d'indice à modifier
   int nouvelle_valeur = 99;  // Nouvelle valeur à insérer
   modifier_ttab(latab, indice_a_modifier, nouvelle_valeur);
   printf("\n5. Afficher le tableau apres la modification a l'indice %d:\n", indice_a_modifier);
   afficher_ttab(*latab);

   // supprimer le premier occurence d'une valeur
   int valeur_a_supprimer = 15; // Exemple de valeur à supprimer
   supprimer_premier_occ_ttab(latab, valeur_a_supprimer);
   printf("\n6. Afficher le tableau apres la suppression du premier occurence de la valeur %d:\n", valeur_a_supprimer);
   afficher_ttab(*latab);

   // supprimer tout les occurences d'une valeur
   printf("\n7. Supprimer tout les occurences de la valeur %d:\n", valeur_a_supprimer);
   int nb_supprimees = supprimer_tout_occurences_ttab(latab, valeur_a_supprimer);
   if (nb_supprimees >= 0)
      printf("Nombre d'occurrences supprimees: %d\n", nb_supprimees);
   else
      errors_message_ttab(nb_supprimees);
   printf("Afficher le tableau apres la suppression de tout les occurences de la valeur %d:\n", valeur_a_supprimer);
   afficher_ttab(*latab);

   // modifier le premier occurence d'une valeur
   int ancienne_valeur = 34; // Exemple de valeur à modifier
   int nouvelle_valeur_modif = 77;  // Nouvelle valeur à insérer
   modifier_premier_occ_ttab(latab, ancienne_valeur, nouvelle_valeur_modif);
   printf("\n8. Afficher le tableau apres la modification du premier occurence de la valeur %d:\n", ancienne_valeur);
   afficher_ttab(*latab);

   // modifier tout les occurences d'une valeur
   modifier_tout_occurences_ttab(latab, ancienne_valeur, nouvelle_valeur_modif);
   printf("\n9. Afficher le tableau apres la modification de tout les occurences de la valeur %d:\n", nouvelle_valeur_modif);
   afficher_ttab(*latab);
   // Libérer la mémoire allouée pour le tableau
   free(latab);
   return 0;
}