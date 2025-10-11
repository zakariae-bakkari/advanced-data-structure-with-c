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
   Noeud *tete;
   Noeud *queue;
} File;

// creation d'un noeud
Noeud *createNoeud()
{
   Noeud *cel = (Noeud *)malloc(sizeof(Noeud));
   if (!cel)
      return ((int)-1);
   cel->suivant=NULL;
   return ((Noeud *)cel);
}
// alocation d'une file et l'initialisation des pointeur
File *createFile()
{
   File *file = (File *)malloc(sizeof(File));
   if (!file)
      return ((int)-1);
   file->tete = NULL;
   file->queue = NULL;
   return ((File *)file);
}
int est_vide_file(File file){
   return ((int)(file.queue == NULL));
}
// enfiler la file : ajouter au dernier
int enfilerFile(File *file, Noeud cel)
{
   if (!file) return ((int)-1);
   if(est_vide_file(*file)) return -2;
   

   
}
