#include <stdio.h>
#include <stdlib.h>

typedef struct cellule
{
   int valeur;
   struct cellule *suivant;
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
      return ((liste *)nouveau_element);
   }

   // si position > 1
   courant = maliste;
   while (((compteur + 1) != position) && (courant->suivant))
   {
      courant = courant->suivant;
      ++compteur;
   }
   // si position est valide
   if ((compteur + 1) == position)
   {
      nouveau_element = (liste *)createcellule(valeur);
      nouveau_element->suivant = courant->suivant;
      courant->suivant = nouveau_element;
      return ((liste *)maliste); // returner la tete du liste
   }
   // on n'utilise pas else car ona deja fair return !!!!
   printf("la position est invalid");
   return ((liste *)maliste);
}

liste *supprimer(liste *maliste, int position)
{
   liste *courant = maliste;
   int conteur = 1;
   if (est_vide_liste(maliste))
   {
      printf("la liste est vide");
      return ((liste *)maliste);
   }
   if (position == 1)
   {
      liste *celleul_a_supprimer = maliste;
      maliste = maliste->suivant;
      free(celleul_a_supprimer);
      return maliste;
   }

   while (((conteur + 1) < position) && (courant->suivant))
   {
      courant = courant->suivant;
      conteur++;
   }
   if (conteur + 1 == position)
   {
      liste *cellule_a_supprimer = courant->suivant;
      courant->suivant = courant->suivant->suivant;
      free(cellule_a_supprimer);

      return maliste;
   }
   printf("Position invalide\n");
   return maliste;
}

void displayList(liste *maliste)
{
   liste *current = maliste;
   while (current != NULL)
   {
      printf("%d -> ", current->valeur);
      current = current->suivant;
   }
   printf("NULL\n");
}

int main()
{
   liste *maliste = (liste *)init_null();
   maliste = inserer_liste(maliste, 10, 1);
   maliste = inserer_liste(maliste, 12, 1);
   maliste = inserer_liste(maliste, 55, 2);
   displayList(maliste);
   maliste = supprimer(maliste, 1);
   displayList(maliste);
   return 0;
}