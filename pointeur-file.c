#include <stdio.h>
#include <stdlib.h>

// structure d'une cellule qui divise en deux partie (valeur pointeur)
typedef struct cel
{
   int valeur;          //  valeur de la cellule
   struct cel *suivant; // un pointeur qui point sur l'element suivant
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
File *init_file()
{
   File *file = (File *)malloc(sizeof(File));
   if (!file)
   {
      printf("Erreur d'allocation memoire");
      return (NULL);
   }
   file->tete = NULL;  // initialiser la tete a null
   file->queue = NULL; // initialiser la queue a null
   return ((File *)file);
}

// tester si la file est vide
int est_vide_file(File *file)
{

   return ((int)(!file->tete && !file->queue)); // une seul est sufisante
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

// fonction recursive pour calculer la taille de la file
int taille_recursive_file(cellule *cel)
{
   if (cel == NULL)
      return ((int)0);
   return 1 + taille_recursive_file(cel->suivant);
}

// enfiler la file : ajouter au dernier
int enfiler(File *file, int valeur)
{
   // verifer l'allocation de la file
   if (!file)
   {
      printf("la file n'exist pas (pas allouer) \n");
      return ((int) -1);
   }
   cellule *nouvelleCellule = creeCellule(valeur);

   // verifer l'allocation de la nouvelle cellule
   if (!nouvelleCellule)
   {
      printf("Erreur d'allocation memoire pour la nouvelle cellule \n");
      return ((int) -2); // Error d'allocation
   }

   // si la file est vide
   if (est_vide_file(file))
   {
      file->tete = file->queue = nouvelleCellule; // la tete et la queue point sur la nouvelle cellule
   }
   else
   {
      file->queue->suivant = nouvelleCellule; // l'element suivant de la queue pointe sur la nouvelle cellule
      file->queue = nouvelleCellule;          // la queue pointe sur la nouvelle cellule
   }
   return ((int) 1); // succes
}

// fonction pour defiler la file : supprimer du debut
int defiler(File *file)
{
   // verifer l'allocation de la file
   if (!file)
   {
      printf("la file n'exist pas (pas allouer) \n");
      return ((int)-1); // Error d'allocation
   }
   
   // verifer si la file est vide
   if (est_vide_file(file))
   {
      printf("la file est vide \n");
      return ((int)-2); // Error file vide
   }
   
   // defiler l'element du tete en resurvant l'adresse de la cellule a supprimer
   cellule *cellule_a_supprimer = file->tete; // sauvegarder l'adresse de la tete
   file->tete = file->tete->suivant;

   // reset the queue if the tete is null
   if (file->tete == NULL)
   {
      file->queue = NULL;
   }

   free(cellule_a_supprimer);      // liberer la memoire de la cellule supprimer
   return ((int)1); // succes
}

// affichier en utilsant une copie de la file
void afficher(File *file)
{
   if (est_vide_file(file))
   {
      printf("File vide\n");
      return;
   }

   cellule *temp = file->tete;
   while (temp != NULL)
   {
      printf("%d->", temp->valeur);
      temp = temp->suivant;
   }
   printf("NULL\n");
}

// afficher les details de la file
void afficher_file(File *file)
{
   cellule *courant = file->tete;
   printf("Affichage : ");
   printf("Tete-> ");
   while (courant != NULL)
   {
      printf("%d-> ", courant->valeur);
      courant = courant->suivant;
   }
   printf("NULL\n");
   printf("Tete: ");
   if (file->tete != NULL)
   {
      printf("%d\n", file->tete->valeur);
   }
   else
   {
      printf("NULL\n");
   }
   printf("Queue: ");
   if (file->queue != NULL)
   {
      printf("%d\n", file->queue->valeur);
   }
   else
   {
      printf("NULL\n");
   }
   printf("\n");
}

int main()
{
   // Initialiser la file vide
   File *file = init_file();

   printf("\n\n========== Test des fonctions de la file (pointeur) ==========\n\n");

   if (!file)
   {
      printf("Erreur d'allocation memoire pour la file.\n");
      return -1;
   }
   else
   {
      printf("File allouee avec succes.\n");
   }

   // tester si la file est vide
   if (est_vide_file(file))
      printf("\nLa file est initialement vide.\n\n");
   else
      printf("\nLa file n'est pas vide initialement.\n\n");

   // Tester la fonction enfiler()
   printf("1. Test de la fonction enfiler() :\n");
   enfiler(file, 10);
   enfiler(file, 20);
   enfiler(file, 30);
   afficher_file(file); // Devrait afficher: 10 20 30

   // tester si la file est vide apres l'enfiler
   printf("2. Tester si la file est vide apres l'enfiler :\n");
   if (est_vide_file(file))
   {
      printf("La file est vide apres l'enfiler.\n\n");
   }
   else
   {
      printf("La file n'est pas vide apres l'enfiler.\n\n");
   }

   // Tester la fonction defiler()
   printf("3. Test de la fonction defiler() :\n");
   defiler(file);       // Retirer 10
   afficher_file(file); // Devrait afficher: 20 30

   // Tester la taille de la file avec la fonction iterative
   printf("4. Test de la fonction taille :\n");
   printf("Taille de la file: %d\n\n", tailleFile(file));
   // Tester la taille de la file avec la fonction recursive
   printf("5. Test de la fonction taille (recursive) :\n");
   printf("Taille recursive de la file: %d\n", taille_recursive_file(file->tete));

   printf("\n\n========== Fin des tests de la file (pointeur) ==========\n\n");

   // Libérer la mémoire à la fin
   free(file);

   return 0;
}
