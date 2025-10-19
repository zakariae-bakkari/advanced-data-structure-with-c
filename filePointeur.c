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
   
   return ((int)(!file->tete && !file->queue));// une seul est sufisante
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
   if (cel == NULL)
      return ((int)0);
   return 1 + taille_recursive_file(cel->suivant);
}
// enfiler la file : ajouter au dernier
int enfilerFile(File *file, int valeur)
{
   if (!file)
      return -1;
   cellule *newcellule = creeCellule(valeur);
   // si la file est vide
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
   // verifer l'allocation de la file
   if (!file)
      return ((int)-1); //! Error d'allocation
   // verifer si la file est vide
   if (est_vide_file(file))
      return ((int)-2); //! Error file vide

   // defiler l'element du tete en resurvant l'adresse de la cellule a supprimer
   cellule *copy = file->tete; // sauvegarder l'adresse de la tete
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

// affichier en utilsant une copie de la file
void afficher(File *file)
{
   int address_du_tete = &file->tete;
   File *courant = file;
   do
   {
      File *PremierElement = file->tete;
      // afficher touts d'abord
      printf("%d->", file->tete->valeur);
      // changer la tete difiler
      file->tete = file->tete->suivant;
      // enfiler le premier element
      file->queue->suivant = PremierElement;
      file->queue = PremierElement;

   } while (&file->tete != address_du_tete);
}

void executerMenu()
{
   File *file = creeFile();
   int choix, valeur;
   do
   {
      printf("\nMenu:\n");
      printf("1. Enfiler un element\n");
      printf("2. Defiler un element\n");
      printf("3. Afficher la taille de la file\n");
      printf("4. Afficher les elements de la file\n");
      printf("5. Quitter\n");
      printf("Entrez votre choix: ");
      scanf("%d", &choix);
      switch (choix)
      {
      case 1:
         printf("Entrez la valeur a enfiler: ");
         scanf("%d", &valeur);
         enfilerFile(file, valeur);
         break;
      case 2:
         defilerFIle(file);
         break;
      case 3:
         printf("Taille de la file: %d\n", tailleFile(file));
         break;
      case 4:
         printf("Elements de la file: ");
         afficher_file_recursive(file);
         printf("\n");
         break;
      case 5:
         printf("Quitter le programme.\n");
         break;
      default:
         printf("Choix invalide. Veuillez reessayer.\n");
      }
   } while (choix != 5);
}
int main()
{
   executerMenu();
   return 0;
}
