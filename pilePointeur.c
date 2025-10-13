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
      return ((Pile *)NULL); // erreur d'allocation
   nouveauElment->suivant = pile;
   pile = nouveauElment;

   return ((Pile *)pile);
};
Pile *depiler_pile(Pile *pile){
   if (!pile)
      return NULL;
   Pile * temp=pile;
   pile = pile->suivant;
   free(temp);
   return((Pile*)pile);
   
}
void affichier_recursive(Pile *pile)
{
   if (!est_vide_pile(pile))
   {
      printf("%d ", pile->valeur);
      affichier_recursive(pile->suivant);
   }
}
int main()
{
   Pile *pile = init_pile();
   pile = empiler_pile(pile, 10);
   pile = empiler_pile(pile, 30);
   pile = empiler_pile(pile, 50);
   pile = depiler_pile(pile);

   affichier_recursive(pile);
}