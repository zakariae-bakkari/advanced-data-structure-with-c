#include <stdio.h>
#include <stdlib.h>

// structure d'une cellule qui divise en deux partie (valeur pointeur)
typedef struct cel
{
   int valeur;          // la parite du valeur
   struct cel *suivant; // un pointeur qui point sur l'elment suivant
} cellule;

// structure d'une file qui contient  deux pointeur (tete et queue) : concept FIFO
typedef struct File
{
   cellule *tete;
   cellule *queue;
} File;

// creation d'un cellule
cellule *creeCellule(int valeur)
{
   cellule *cel = (cellule *)malloc(sizeof(cellule));
   if (!cel)
      return NULL;
   cel->valeur = valeur;
   cel->suivant = NULL;
   return ((cellule *)cel);
}
// alocation d'une file et l'initialisation des pointeur
File *creeFile()
{
   File *file = (File *)malloc(sizeof(File));
   if (!file)
      return (NULL);
   file->tete = NULL;
   file->queue = NULL;
   return ((File *)file);
}

int est_vide_file(File *file)
{
   return ((int)(file->queue == NULL));
}

// returner la taille d'un fille en parcourant du tete jusqua  la fin (null)
int tailleFile(File *file) // pas correct car il na pas utilise le principe fifo
{
   if (est_vide_file(file))
      return 0;
   cellule *temp = file->tete;
   int taille = 0;
   while (temp != NULL)
   {
      taille++;
      temp = temp->suivant;
   }
   return taille;
}

int taille_recursive_file(cellule *cel)
{
   if (est_vide_file(cel))
      return ((int)0);
   return 1 + taille_recursive_file(cel->suivant);
}
// enfiler la file : ajouter au dernier
int enfilerFile(File *file, int valeur)
{
   if (!file)
      return -1;
   cellule *newcellule = creecellule(valeur);
   if (!newcellule)
      return -1;

   if (est_vide_file(file))
   {
      file->tete = file->queue = newcellule;
   }
   else
   {
      file->queue->suivant = newcellule;
      file->queue = newcellule;
   }
   return ((int)0);
}
int defilerFIle(File *file)
{

   if (!file)
      return ((int)-1);
   if (est_vide_file(file))
      return ((int)-2);
   cellule *copy = file->tete;
   file->tete = file->tete->suivant;
   // reset the queue if the tete is null
   if (file->tete == NULL)
   {
      file->queue = NULL;
   }
   printf("\nfile->tete = %d \nfile->queue = %d \n", file->tete->valeur, file->queue->valeur);
   free(copy);
   return ((int)1);
}

void afficherFIle(File * file)
{
   if (est_vide_file(file)) // AJOUT de vérification
   {
      printf("\nFile vide\n");
      return;
   }

   cellule *temp = file->tete;
   printf("\n");
   printf("tete->");
   while (temp != NULL)
   {
      printf("|%d|->", temp->valeur);
      temp = temp->suivant;
   }
   printf("NULL\n");
   printf("\nqueue -> %d", file->queue->valeur);
   printf("\n");
}

int main()
{
   executerMenu();
   return 0;
}
