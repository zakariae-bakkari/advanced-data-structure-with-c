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

void neuron(liste *l)
{
   // l'existance
   if (!l)
      return;

   int valeur, occ, rang;
   int valeur_max, occ_max, rang_max;
   int rang_global;

   valeur = l->valeur;
   occ = 1;
   rang = 1;

   //----max
   valeur_max = valeur;
   occ_max = occ;
   rang_max = rang;
   rang_global = 1;
   liste *crt = l->suivant;
   while (crt)
   {
      rang_global++;
      if (crt->valeur == valeur)
      {
         occ++;
      }
      else
      {
         // nouvelle valeur
         // tester si c'est le max
         if (occ > occ_max)
         {
            valeur_max = valeur;
            occ_max = occ;
            rang_max = rang;
         }
         // reinitialiser
         valeur = crt->valeur;
         occ = 1;
         rang = rang_global;
      }
      crt = crt->suivant;
   }

   printf("la valeur la plus frequente est %d avec %d occurences a la position %d\n", valeur_max, occ_max, rang_max);
}
void afficher_liste(liste *maliste)
{
   liste *current = maliste;
   printf("Liste-> ");
   while (current != NULL)
   {
      printf("%d -> ", current->valeur);
      current = current->suivant;
   }
   printf("NULL\n");
}
int main()
{
   liste *maListe = init_null();
   maListe = inserer_liste(maListe, 2, 1);
   maListe = inserer_liste(maListe, 2, 2);
   maListe = inserer_liste(maListe, 5, 3);
   maListe = inserer_liste(maListe, 5, 4);
   maListe = inserer_liste(maListe, 5, 5);
   maListe = inserer_liste(maListe, 1, 6);
   maListe = inserer_liste(maListe, 1, 7);
   maListe = inserer_liste(maListe, 3, 8);
   afficher_liste(maListe);
   neuron(maListe);
   return 0;
}