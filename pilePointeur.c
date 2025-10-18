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
      return ((Pile *)NULL); // erreur d'allocation de la cellule
   nouveauElment->suivant = pile;
   pile = nouveauElment;

   return ((Pile *)pile);
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
   while (mapile)
   {
      printf("%d ", mapile->valeur);
      tmp = empiler_pile(tmp, mapile->valeur);
      mapile = depiler_pile(mapile);
   }
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
   executerMenu();
   return 0;
}