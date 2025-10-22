#include <stdio.h>
#include <stdlib.h>

typedef struct cellule
{
   int valeur;
   struct cellule *suivant;
   struct cellule *precedent;
} cellule;

typedef cellule liste;

cellule *init_null()
{
   return ((cellule *)NULL);
}

cellule *createcellule(int valeur)
{
   cellule *cel = (cellule *)malloc(sizeof(cellule));
   if (!cel)
      return NULL;
   cel->valeur = valeur;
   cel->suivant = NULL;
   cel->precedent = NULL;
   return ((cellule *)cel);
}

// tester si la liste est vide
int est_vide_liste(liste *maliste)
{
   return ((int)(maliste == NULL));
};

// insertion a une position
liste *inserer_liste(liste *maliste, int valeur, int position) // complexite O(n)
{
   liste *nouveau_element, *courant;
   int compteur = 1;
   if (position < 1) // la position allon de 1 jusqua ...
   {
      return ((liste *)maliste);
   }

   // si le premier
   if (position == 1)
   {
      nouveau_element = createcellule(valeur);
      nouveau_element->suivant = maliste;
      // AJOUT CRITIQUE : Gérer le pointeur précédent !
      if (maliste != NULL)
      {
         maliste->precedent = nouveau_element;
      }
      nouveau_element->precedent = NULL; // Premier élément

      return ((liste *)nouveau_element);
   }
   // si position > 1
   courant = maliste;
   while (((compteur) != position) && (courant->suivant))
   {
      courant = courant->suivant;
      ++compteur;
   }
   // si position est valide
   if ((compteur) == position)
   {
      nouveau_element = (liste *)createcellule(valeur);
      if (!nouveau_element)
         return maliste;
      nouveau_element->suivant = courant->suivant;
      nouveau_element->precedent = courant;
      // CORRECTION : Vérifier si courant->suivant existe !
      if (courant->suivant != NULL)
      {
         courant->suivant->precedent = nouveau_element;
      }
      courant->suivant = nouveau_element;
      return ((liste *)maliste); // returner la tete du liste
   }
   // on n'utilise pas else car ona deja fair return !!!!
   printf("la position est invalid");
   return ((liste *)maliste);
}
