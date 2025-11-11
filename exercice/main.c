#include <stdio.h>
#define TAILLE 6 // Taille du tableau mais la dernière case restera toujours vide

typedef struct
{
   int tab[TAILLE];
   int sommet; // indice du sommet
} Pile;

// Initialisation
void initialiser(Pile *p)
{
   p->sommet = -1; // pile vide
}

// Tester si la pile est vide
int pileVide(Pile *p)
{
   return (p->sommet == -1);
}

// Tester si la pile est pleine (on laisse la dernière case vide)
int pilePleine(Pile *p)
{
   return (p->sommet == TAILLE - 2);
}

// Empiler
void empiler(Pile *p, int x)
{
   if (pilePleine(p))
   {
      printf("Pile pleine !\n");
      return;
   }
   p->sommet++;
   p->tab[p->sommet] = x;
}

// Depiler
void depiler(Pile *p)
{
   if (pileVide(p))
   {
      printf("Pile vide !\n");
      return;
   }
   int val = p->tab[p->sommet];
   p->sommet--;
}

// Affichage (respect LIFO : on affiche du sommet vers le bas)
void afficher(Pile *p)
{
   if (pileVide(p))
   {
      printf("Pile vide !\n");
      return;
   }

   printf("Contenu de la pile (sommet -> base) : ");
   int ind = TAILLE - 1;

   while (p->sommet >= 0)
   {
      printf("%d  ", p->tab[p->sommet]);
      // depiler(p)
      p->tab[ind] = p->tab[p->sommet];
      p->sommet--;
      ind--;
   }

   while (ind <= (TAILLE - 1))
   {
      empiler(p, p->tab[ind]);
      ind++;
   }

   printf("\n");
}

// Programme principal
int main()
{
   Pile p;
   initialiser(&p);

   empiler(&p, 10);
   empiler(&p, 20);
   empiler(&p, 30);
   empiler(&p, 40);

   afficher(&p);
   afficher(&p);
   afficher(&p);

   printf("%d\n", p.tab[p.sommet]);

   return 0;
}