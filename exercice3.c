#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAILLE 100

// Demande et valide le nombre d'éléments du tableau (entre 1 et TAILLE)
int tableau_saisir_taille()
{
   printf("Entrez le nombre d'elements a saisir (max %d) : ", TAILLE);
   int nbsaisie;
   do
   {
      scanf("%d", &nbsaisie);
      if (nbsaisie < 1 || nbsaisie > TAILLE)
         printf("Nombre invalide. Veuillez reessayer: ");
   } while (nbsaisie < 1 || nbsaisie > TAILLE);
   return nbsaisie;
}

// Remplit le tableau avec les valeurs saisies par l'utilisateur (-999 à 999)
void tableau_saisir_elements(int tab[TAILLE], int taille)
{
   int valeur;
   for (int i = 0; i < taille; i++)
   {
      do
      {
         printf("Entrez l'element %d: ", i + 1);
         scanf("%d", &valeur);
         if (valeur > 999 || valeur < -999)
            printf("Valeur hors limite [-999,999]. Reessayez: ");
      } while (valeur > 999 || valeur < -999);
      tab[i] = valeur;
   }
}

// Affiche le contenu du tableau
void tableau_afficher(int tab[TAILLE], int taille)
{
   for (int i = 0; i < taille; i++)
   {
      printf("t[%d] = %+4d \n", i, tab[i]);
   }
}

// Trouve l'indice du minimum dans le tableau
int tableau_trouver_min_indice(int tab[TAILLE], int taille)
{
   int min = tab[0];
   int indice = 0;
   for (int i = 1; i < taille; i++)
   {
      if (tab[i] < min)
      {
         min = tab[i];
         indice = i;
      }
   }
   return indice;
}

// Supprime l'élément à l'index spécifié en décalant vers la gauche et décrémentant la taille
void tableau_supprimer_element(int tab[TAILLE], int *taille, int index)
{
   if (index < 0 || index >= *taille)
   {
      printf("Index invalide.\n");
      return;
   }

   for (int i = index; i < *taille - 1; i++) // o(n)
   {
      tab[i] = tab[i + 1]; // Décalage des éléments vers la gauche
   }
   (*taille)--;
}

// Ajoute un élément à une position en décalant vers la droite et incrémentant la taille
void tableau_ajouter_element(int tab[TAILLE], int *taille, int position, int valeur)
{
   if (position < 0 || position > *taille)
   {
      printf("Position invalide.\n");
      return;
   }

   if (*taille >= TAILLE)
   {
      printf("Tableau plein, impossible d'ajouter.\n");
      return;
   }

   // Décaler les éléments vers la droite
   for (int i = *taille; i > position; i--)
   {
      tab[i] = tab[i - 1];
   }

   tab[position] = valeur;
   (*taille)++;
}

// Supprime toutes les occurrences d'une valeur en utilisant la suppression élémentaire
void tableau_supprimer_valeur(int tab[TAILLE], int *nbsaisie, int valeur) // o(n^2) -> o(n) -> o(log n)
{
   bool trouve = false;                // o(1)
   for (int i = 0; i < *nbsaisie; i++) // o(n)
   {
      if (tab[i] == valeur)
      {
         trouve = true;
         tableau_supprimer_element(tab, nbsaisie, i); // o(n)
         i--;                                         // Pour réexaminer la position courante après décalage
      }
   }
   if (!trouve)
   {
      printf("La valeur %d n'a pas ete trouvee dans le tableau.\n", valeur);
   }
}

void tableau_supprimer_valeur_optimise(int tab[TAILLE], int *nbsaisie, int valeur)
{             // o(n) garde les elements qui ne sont pas egale a valeur
   int j = 0; // Indice pour le tableau filtré
   int ind = 0;
   for (ind = 0; ind < *nbsaisie; ind++)
   {
      if (tab[ind] != valeur)
      {
         tab[j] = tab[ind]; // Conserver l'élément
         j++;
      }
   }
   if (j == *nbsaisie)
   {
      printf("La valeur %d n'a pas ete trouvee dans le tableau.\n", valeur);
   }
   *nbsaisie = j; // Mettre à jour la taille du tableau
}
// Garde uniquement la première occurrence d'une valeur et supprime les répétitions
void tableau_garder_premiere_occurrence(int tab[TAILLE], int *taille, int valeur)
{
   bool premiere_occurrence = false; // Indique si la première occurrence a été trouvée
   for (int i = 0; i < *taille; i++)
   {
      if (tab[i] == valeur) // valeur est trouvée
      {

         if (premiere_occurrence == false) // if premiere_occurrence est false
         {
            premiere_occurrence = true; // Marque la première occurrence comme trouvée
         }
         else
         {
            tableau_supprimer_element(tab, taille, i);
            i--; // Pour réexaminer la position courante après décalage
         }
      }
   }
   if (!premiere_occurrence)
   {
      printf("La valeur %d n'a pas ete trouvee dans le tableau.\n", valeur);
   }
}
void tableau_garder_premiere_occurrence_optimise(int tab[TAILLE], int *taille, int valeur)
{
   int j = 0; // Indice pour le tableau filtré
   bool trouve = false;
   int i = 0;
   for (i = 0; i < *taille; i++)
   {
      if (tab[i] == valeur)
      {
         if (!trouve)
         {
            j++;
            trouve = true;
         }
      }
      else
      {
         tab[j] = tab[i]; // Conserver les autres éléments
         j++;
      }
   }
   if (!trouve)
   {
      printf("La valeur %d n'a pas ete trouvee dans le tableau.\n", valeur);
   }
   *taille = j; // Mettre à jour la taille du tableau
}
int main()
{
   int tab[TAILLE], nbsaisie;

   // Saisir et afficher le tableau initial
   nbsaisie = tableau_saisir_taille();
   tableau_saisir_elements(tab, nbsaisie);
   printf("\nTableau initial:\n");
   tableau_afficher(tab, nbsaisie);

   // Supprimer les répétitions du nombre
   // printf("\nEntrer un nombre a supprimer: ");
   int nombre_a_supprimer;
   // scanf("%d", &nombre_a_supprimer);
   // tableau_supprimer_valeur(tab, &nbsaisie, nombre_a_supprimer);
   // tableau_afficher(tab, nbsaisie);

   // Supprimer les répétitions du nombre (garder première occurrence)
   printf("\nEntrer un nombre a supprimer (toutes occurrences sauf la premiere): ");
   scanf("%d", &nombre_a_supprimer);
   tableau_garder_premiere_occurrence_optimise(tab, &nbsaisie, nombre_a_supprimer);
   tableau_afficher(tab, nbsaisie);

   return 0;
}
