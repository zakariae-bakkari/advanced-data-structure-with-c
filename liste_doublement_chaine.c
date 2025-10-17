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