#include <stdio.h>
#include <stdlib.h>

// structure d'une cellule qui divise en deux partie (donnes pointeur)
typedef struct Noeud
{
   int donnes;     // la parite du donnes
   Noeud *suivant; // un pointeur qui point sur l'elment suivant
} Noeud;

// structure d'une file qui contient  deux pointeur (tete et queue) : concept FIFO
typedef struct File
{
   Noeud tete;
   Noeud queue;
} File;

// creation d'un noeud
Noeud *createNoeud()
{
   Noeud *cel = (Noeud *)malloc(sizeof(Noeud));
   return ((Noeud *)cel);
}
File *createFile()
{
   File *file = (File *)malloc(sizeof(File));

   return ((File *)file);
}
