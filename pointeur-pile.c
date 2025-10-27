#include <stdio.h>
#include <stdlib.h>

typedef struct cel
{
   int valeur;
   struct cel *suivant;
} cellule;

typedef cellule Pile; // type pile

// creation du cellule
cellule *cree_cellule(int valeur)
{
   cellule *newCellule = (cellule *)malloc(sizeof(cellule));
   if (!newCellule)
      return NULL;

   newCellule->valeur = valeur;
   newCellule->suivant = NULL;

   return ((cellule *)newCellule);
}

Pile *init_pile()
{
   return ((Pile *)NULL);
}
// teseter si la pile est vide
int est_vide_pile(Pile *pile)
{
   return (pile == NULL);
}

// rerturner la taille d'un pile
int taille_recursive_pile(Pile *pile)
{ // il faut faire * pointeur pour ne pas ....
   if (est_vide_pile(pile))
      return 0;
   return ((int)(1 + taille_recursive_pile(pile->suivant)));
}

// empiler
Pile *empiler_pile(Pile *pile, int valeur)
{
   cellule *nouveauElment = cree_cellule(valeur);
   if (!nouveauElment)
      return pile; // returner la pile originale si erreur d'allocation

   nouveauElment->suivant = pile;
   pile = nouveauElment;

   return ((Pile *)pile); // returner le nouveau sommet
};
Pile *depiler_pile(Pile *pile)
{
   if (!pile)
      return NULL;
   Pile *temp = pile;
   pile = pile->suivant;
   free(temp);
   return ((Pile *)pile);
}


int recherche_recursive_pile_2(Pile *pile, int valeur, int position)// dernier element
{
   if (est_vide_pile(pile))//
      return ((int)0); // valeur non trouvee
   if (pile->valeur == valeur)
      return (position); // valeur trouvee
   return recherche_recursive_pile_2(pile->suivant, valeur, position + 1);
}

int recherche_recursive_pile(Pile *pile, int valeur)
{
   return recherche_recursive_pile_2(pile, valeur, 1);
}

void affichier_recursive(Pile *pile)
{
   if (!est_vide_pile(pile))
   {
      printf("%d ", pile->valeur);
      affichier_recursive(pile->suivant);
   }
}
void afficher_pile(Pile *mapile)
{
   Pile *tmp;
   tmp = init_pile();
   printf("Pile-> ");
   while (mapile)
   {
      printf("%d-> ", mapile->valeur);
      tmp = empiler_pile(tmp, mapile->valeur);
      mapile = depiler_pile(mapile);
   }
   printf("NULL\n");
   while (tmp)
   {
      mapile = empiler_pile(mapile, tmp->valeur);
      tmp = depiler_pile(tmp);
   }
   free(tmp);
}

// Fonction pour afficher les options du menu
void afficherMenu()
{
   printf("\n--- Menu des Operations de pile ---\n");
   printf("1. Empiler (Ajouter element)\n");
   printf("2. Depiler (Supprimer element)\n");
   printf("3. Afficher le contenu de la pile\n");
   printf("4. Obtenir la taille de la pile\n");
   printf("0. Quitter\n");
   printf("Entrez votre choix: ");
}

// Fonction pour gerer les operations du menu
void executerMenu()
{
   Pile *mapile = init_pile();
   int choix, valeur;

   printf("Nouvelle pile creee avec succes.\n");

   do
   {
      afficherMenu();
      scanf("%d", &choix);

      switch (choix)
      {
      case 1:
         printf("Entrez la valeur a empiler: ");
         scanf("%d", &valeur);
         mapile = empiler_pile(mapile, valeur);
         if (mapile)
            printf("Valeur %d empilee avec succes.\n", valeur);
         else
            printf("Echec de l'empilage.\n");
         break;

      case 2:
         if (!est_vide_pile(mapile))
         {
            mapile = depiler_pile(mapile);
            printf("Element depile avec succes.\n");
         }
         else
            printf("La pile est vide!\n");
         break;

      case 3:
         if (!est_vide_pile(mapile))
            afficher_pile(mapile);
         else
            printf("La pile est vide!\n");
         break;

      case 4:
         printf("Taille de la pile: %d\n", taille_recursive_pile(mapile));
         break;
      case 0:
         printf("Fin du programme...\n");
         // Liberer la memoire avant de quitter
         while (!est_vide_pile(mapile))
            mapile = depiler_pile(mapile);
         break;

      default:
         printf("Choix invalide! Veuillez reessayer.\n");
      }
   } while (choix != 0);
}

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


   printf("\n\n========== fin du testes ==========\n");
   return 0;
}