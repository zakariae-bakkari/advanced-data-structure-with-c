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

int taille_recursive_file(cellule *cel)
{
   if (cel == NULL)
      return ((int)0);
   return 1 + taille_recursive_file(cel->suivant);
}
// enfiler la file : ajouter au dernier
int enfiler(File *file, int valeur)
{
   if (!file)
   {
      printf("la file n'exist pas (pas allouer) \n");
      return -1;
   }
   cellule *nouvelleCellule = creeCellule(valeur); // creer une nouvelle cellule et le teste d'allocation fait dans la fonction creeCellule
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
   return ((int)0); // succes
}

// fonction pour defiler la file : supprimer du debut
int defiler(File *file)
{
   // verifer l'allocation de la file
   if (!file)
   {
      printf("la file n'exist pas (pas allouer) \n");
      return ((int)-1); //! Error d'allocation
   }
   // verifer si la file est vide
   if (est_vide_file(file))
   {
      printf("la file est vide \n");
      return ((int)-2); //! Error file vide
   }
   // defiler l'element du tete en resurvant l'adresse de la cellule a supprimer
   cellule *copy = file->tete; // sauvegarder l'adresse de la tete
   file->tete = file->tete->suivant;
   // reset the queue if the tete is null
   if (file->tete == NULL)
   {
      file->queue = NULL;
   }
   // CORRECTION CRITIQUE: Vérifier avant d'afficher !
   printf("---------------------------\n");
   printf("file->tete = ");
   if (file->tete != NULL)
      printf("%d", file->tete->valeur);
   else
      printf("NULL");

   printf("\nfile->queue = ");
   if (file->queue != NULL)
      printf("%d \n", file->queue->valeur);
   else
      printf("NULL\n");

   free(copy);      // liberer la memoire de la cellule supprimer
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
void afficher_file(File *file)
{
   cellule *courant = file->tete;
   printf("Contenu de la file : ");
   while (courant != NULL)
   {
      printf("%d ", courant->valeur);
      courant = courant->suivant;
   }
   printf("\n");
   printf("Tete de la file : ");
   if (file->tete != NULL)
   {
      printf("%d\n", file->tete->valeur);
   }
   else
   {
      printf("NULL\n");
   }
   printf("Queue de la file : ");
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
void executerMenu()
{
   File *file = init_file();
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
         enfiler(file, valeur);
         break;
      case 2:
         defiler(file);
         break;
      case 3:
         printf("Taille de la file: %d\n", tailleFile(file));
         break;
      case 4:
         printf("Elements de la file: ");
         afficher_file(file);
         break;
      default:
         printf("Choix invalide. Veuillez reessayer.\n");
      }
   } while (choix != 5);
}
int main()
{
   File *file = init_file();

   printf("Initialisation d'une file vide:\n");
   printf("Est vide: %s\n", est_vide_file(file) ? "Oui" : "Non");
   printf("Taille: %d\n\n", tailleFile(file));

   printf("Enfilage de 3 elements (10, 20, 30):\n");
   enfiler(file, 10);
   enfiler(file, 20);
   enfiler(file, 30);
   afficher_file(file);

   printf("Est vide: %s\n", est_vide_file(file) ? "Oui" : "Non");
   printf("Taille: %d\n\n", tailleFile(file));

   printf("Defilage d'un element:\n");
   defiler(file);
   afficher_file(file);

   printf("Taille apres defilage: %d\n\n", tailleFile(file));

   printf("Ajout d'un nouvel element (40):\n");
   enfiler(file, 40);
   afficher_file(file);

   printf("Vidage complet de la file:\n");
   defiler(file);
   defiler(file);
   defiler(file);

   printf("Est vide: %s\n", est_vide_file(file) ? "Oui" : "Non");

   free(file);
   return 0;
}
