#include <stdio.h>
#include <stdlib.h>

// structure d'une cellule qui divise en deux partie (donnes pointeur)
typedef struct Noeud
{
   int donnes;            // la parite du donnes
   struct Noeud *suivant; // un pointeur qui point sur l'elment suivant
} Noeud;

// structure d'une file qui contient  deux pointeur (tete et queue) : concept FIFO
typedef struct File
{
   Noeud *tete;
   Noeud *queue;
} File;

// creation d'un noeud
Noeud *createNoeud(int data)
{
   Noeud *cel = (Noeud *)malloc(sizeof(Noeud));
   if (!cel)
      return NULL;
   cel->donnes = data;
   cel->suivant = NULL;
   return ((Noeud *)cel);
}
// alocation d'une file et l'initialisation des pointeur
File *createFile()
{
   File *file = (File *)malloc(sizeof(File));
   if (!file)
      return (NULL);
   file->tete = NULL;
   file->queue = NULL;
   return ((File *)file);
}
int est_vide_file(File file)
{
   return ((int)(file.queue == NULL));
}

// returner la taille d'un fille en parcourant du tete jusqua  la fin (null)
int tailleFile(File file)
{
   if (est_vide_file(file))
      return 0;
   Noeud *temp = file.tete;
   int taille = 0;
   while (temp != NULL)
   {
      taille++;
      temp = temp->suivant;
   }
   return taille;
}
// enfiler la file : ajouter au dernier
int enfilerFile(File *file, int valeur)
{
   if (!file)
      return -1;
   Noeud *newNoeud = createNoeud(valeur);
   if (!newNoeud)
      return -1;

   if (est_vide_file(*file))
   {
      file->tete = file->queue = newNoeud;
   }
   else
   {
      file->queue->suivant = newNoeud;
      file->queue = newNoeud;
   }
   return ((int)0);
}
int defilerFIle(File *file)
{

   if (!file)
      return ((int)-1);
   if (est_vide_file(*file))
      return ((int)-2);
   Noeud *copy = file->tete;
   file->tete = file->tete->suivant;
   // reset the queue if the tete is null
   if (file->tete == NULL)
   {
      file->queue = NULL;
   }
   printf("\nfile->tete = %d \nfile->queue = %d \n", file->tete->donnes, file->queue->donnes);
   free(copy);
   return ((int)1);
}

void afficherFIle(File file)
{
   if (est_vide_file(file)) // AJOUT de vérification
   {
      printf("\nFile vide\n");
      return;
   }

   Noeud *temp = file.tete;
   printf("\n");
   printf("tete->");
   while (temp != NULL)
   {
      printf("|%d|->", temp->donnes);
      temp = temp->suivant;
   }
   printf("NULL\n");
   printf("\nqueue -> %d", file.queue->donnes);
   printf("\n");
}


int main()
{
   executerMenu();
   return 0;
}
