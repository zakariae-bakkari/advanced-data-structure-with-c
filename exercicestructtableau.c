#include <stdio.h>
#include <stdlib.h>
#define TAILLE 10

// structure du tableau avec son indice du dernier element en definition leur type
typedef struct Matab
{
   int tab[TAILLE];
   int indice_dr;
} Matab;

// *********************************************************************************
Matab *create_tab()
{
   Matab *latab = (Matab *)malloc(sizeof(Matab));
   if (!latab)
      exit(-1); //! Erreur d'allocation mémoire
   return ((Matab *)latab);
}

// *********************************************************************************

// inisialiser le tableau
int init_ttab(Matab *latab)
{
   if (!latab)
      return ((int)-1);   //! Erreur : le tableau n'existe pas (utilisant un pointeur NULL)
   latab->indice_dr = -1; //? Initialiser l'indice du dernier élément
   return ((int)0);       //* Succès
}

// *********************************************************************************

int est_vide_ttab(Matab latab) // works
{
   return ((int)(latab.indice_dr == -1)); // Retourne 1(true) si le tableau est vide, sinon 0 (false)
}

// *********************************************************************************

int nombre_elements_ttab(Matab latab) // works
{
   return ((int)(latab.indice_dr + 1)); // Retourne le nombre d'éléments dans le tableau
}

// *********************************************************************************

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
// *********************************************************************************

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

// *********************************************************************************
int recherche_ttab(Matab latab, int valeur)
{
   int ind;
   for (ind = 0; ind <= latab.indice_dr; ind++)
      if (latab.tab[ind] == valeur)
         return ((int)ind); //* Succès : valeur trouvée, retourne l'indice
   return ((int)-1);        //! Erreur : valeur non trouvée
}

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

// *********************************************************************************

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

// *********************************************************************************
void afficher_ttab(Matab latab)
{
   int ind;

   for (ind = 0; ind <= latab.indice_dr; ind++)
      printf("t[%d] = %d \n", ind, latab.tab[ind]);
}
// *********************************************************************************
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
   int choix, valeur, resultat, indice;
   Matab *ptrTab = create_tab();
   init_ttab(ptrTab);

   // === en repete de demander un nombre tanque leur est diff de 8 (quitter) ==
   do
   {
      choix = menu();
      switch (choix)
      {
      case 1: // replissage
         remplir_ttab(ptrTab);
         break;
      case 2: // affichage
         afficher_ttab(*ptrTab);
         break;
      case 3: // rechercher
         printf("Entrez la valeur a rechercher: ");
         scanf("%d", &valeur);
         resultat = recherche_ttab(*ptrTab, valeur);
         if (resultat != -1)
            printf("la valeur %d est trouve dans l'indice : %d", valeur, resultat);
         else
            printf("la valeur %d n'est pas trouve dans le tableau ", valeur);
         break;
      case 4: // insertion
         printf("Entrez l'indice d'insertion (0 a %d): ", ptrTab->indice_dr + 1);
         scanf("%d", &indice);
         printf("Entrez la valeur a inserer: ");
         scanf("%d", &valeur);
         resultat = insertion(ptrTab, indice, valeur);
         if (resultat == 0)
            printf(" -> Element %d ajoute avec succes a l'indice %d\n", valeur, indice);
         else
         {
            printf(" -> Erreur d'insertion, code d'erreur: %d\n", resultat);
            errors_message_ttab(resultat);
         }
         break;
      case 5: // supprission
         printf("Entrez l'indice de l'element a supprimer (0 a %d): ", ptrTab->indice_dr);
         scanf("%d", &indice);
         resultat = supprimer_ttab(ptrTab, indice);
         if (resultat == 0)
            printf(" -> Element a l'indice %d supprime avec succes\n", indice);
         else
         {
            printf(" -> Erreur de suppression, code d'erreur: %d\n", resultat);
            errors_message_ttab(resultat);
         }
         break;
      case 6: // modification
         printf("Entrez l'indice de l'element a modifier (0 a %d): ", ptrTab->indice_dr);
         scanf("%d", &indice);
         printf("Entrez la nouvelle valeur: ");
         scanf("%d", &valeur);
         resultat = modifier_ttab(ptrTab, indice, valeur);
         if (resultat == 0)
            printf(" -> Element a l'indice %d modifie avec succes\n", indice);
         else
         {
            printf(" -> Erreur de modification, code d'erreur: %d\n", resultat);
            errors_message_ttab(resultat);
         }
         break;
      case 7: // nombre des elements
         printf("le nombre d'element dans le tableau est : %d", nombre_elements_ttab(*ptrTab));
         break;
      }
   } while (choix != 8);
}