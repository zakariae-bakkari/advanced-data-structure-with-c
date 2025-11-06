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

// insertion a bonne place dans la file
void inserer_bonne_place_file(File *file, int valeur){
   File *temp = init_file();
   if (!file) {
      printf("la file n'exist pas (pas allouer) \n");
      return;
   }
   
   // Cas 1: File vide
   if (est_vide_file(file)) {
      enfiler(file, valeur);
      free(temp);
      return;
   }
   
   // Cas 2: Insertion au debut
   if (valeur < file->tete->valeur) {
      cellule *NE = creeCellule(valeur);
      if (NE) {
         NE->suivant = file->tete;
         file->tete = NE;
      }
      free(temp);
      return;
   }
   
   // Cas 3: Insertion a la fin
   if (valeur >= file->queue->valeur) {
      enfiler(file, valeur);
      free(temp);
      return;
   }
   
   // Cas 4: Insertion au milieu
   // Défiler jusqu'à trouver la bonne place
   while (!est_vide_file(file) && file->tete->valeur < valeur) {
      enfiler(temp, file->tete->valeur);
      defiler(file);
   }
   
   // Insérer la nouvelle valeur
   enfiler(temp, valeur);
   
   // Transférer le reste
   while (!est_vide_file(file)) {
      enfiler(temp, file->tete->valeur);
      defiler(file);
   }
   
   //Remettre tout dans la file originale
   while (!est_vide_file(temp)) {
      enfiler(file, temp->tete->valeur);
      defiler(temp);
   }
   
   // Libérer la file temporaire
   free(temp);
}

// tris de la file en utilisant l'insertion a bonne place
void trier_file(File *file){
   File *temp = init_file();
   if (!file) {
      printf("la file n'exist pas (pas allouer) \n");
      return;
   }
   
   while (!est_vide_file(file)) {
      int valeur = file->tete->valeur;
      defiler(file);
      inserer_bonne_place_file(temp, valeur);
   }
   
   // Remettre tout dans la file originale
   while (!est_vide_file(temp)) {
      enfiler(file, temp->tete->valeur);
      defiler(temp);
   }
   
   // Libérer la file temporaire
   free(temp);
}

//fonction recherche recursive dans la file
int recherche_recursive_file_2(cellule *cel, int valeur, int position)
{
   if (cel == NULL)
      return ((int)0); // valeur non trouvee
   if (cel->valeur == valeur)
      return (position); // valeur trouvee
   return recherche_recursive_file_2(cel->suivant, valeur, position + 1);
}
int recherche_recursive_file(File *file, int valeur)
{
   return recherche_recursive_file_2(file->tete, valeur, 1);
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
   enfiler(file, 1);
   enfiler(file, 50);
   enfiler(file, 67);

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

   // Tester la fonction recherche_recursive_file()
   printf("\n6. Test de la fonction recherche_recursive_file() :\n");
   int valeur_recherchee = 20;
   int position_trouvee = recherche_recursive_file(file, valeur_recherchee);
   if (position_trouvee != 0)
      printf("Valeur %d trouvee a la position %d dans la file.\n", valeur_recherchee, position_trouvee);
   else
      printf("Valeur %d non trouvee dans la file.\n", valeur_recherchee);
   afficher_file(file);
   

   printf("\n\n========== Fin des tests de la file (pointeur) ==========\n\n");

   // Libérer la mémoire à la fin
   // free(file);

   // tester la fonction inserer_bonne_place_file
   printf("7. Test de la fonction inserer_bonne_place_file() :\n");
   File *file2 = init_file();
   inserer_bonne_place_file(file2, 25);
   inserer_bonne_place_file(file2, 5);
   inserer_bonne_place_file(file2, 60);
   inserer_bonne_place_file(file2, 15);
   afficher_file(file2);

   // tester la fonction trier_file
   printf("8. Test de la fonction trier_file() :\n");
   trier_file(file);
   afficher_file(file);


   return 0;
}
