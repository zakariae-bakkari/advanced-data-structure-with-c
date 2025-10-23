#include <stdio.h>
#include <stdlib.h>
#define maxelem 10

typedef struct file
{
   int tableau[maxelem];
   int tete;
   int queue;
} file;

// *********************************************************************************
file *create_file()
{
   file *lafile = (file *)malloc(sizeof(file));
   if (!lafile)
      exit(-1); //! Erreur d'allocation mémoire
   return ((file *)lafile);
}

// *********************************************************************************

// inisialiser le tableau et tete et queue
int init_file(file *lafile)
{
   if (!lafile)
      return ((int)-1); //! Erreur : le tableau n'existe pas (utilisant un pointeur NULL)
   lafile->tete = 0;
   lafile->queue = -1;
   return ((int)0); //* Succès
}

// *********************************************************************************
// tester si la file est vide
int est_vide_file(file lafile) // works
{
   return ((int)(lafile.queue < lafile.tete)); // Retourne 1(true) si le tableau est vide, sinon 0 (false)
}

// *********************************************************************************
// tester si la file est sature
int est_sature_file(file lafile)
{
   return ((int)(lafile.queue - lafile.tete == maxelem - 1)); // il va returne 1 si tete + queue = max du taille - 1
}

// *********************************************************************************
// returner le nombre d'element dans la file
int nombre_elements_file(file lafile) // works
{
   return ((int)(lafile.queue - lafile.tete + 1)); // Retourne le nombre d'éléments dans le tableau
}

// *********************************************************************************
// tasser la file vers gauche pour ajouter l'espace unutilisable
int tasser_file(file *lafile)
{
   int ind;
   if (!lafile)
      return ((int)-1); //! Erreur : la file n'exist pas
   for (ind = lafile->tete; ind <= lafile->queue; ind++)
      lafile->tableau[ind - lafile->tete] = lafile->tableau[ind];
   lafile->queue = lafile->queue - lafile->tete; // CHANGER LA VALEUR QUEUE
   lafile->tete = 0;

   return ((int)2);
}

// enfiler la file: ajouter a la fin (concept FIFO: first in first out)
int enfiler_file(file *lafile, int valeur)
{
   int tasser = 1; // par defaut est non tasser (1 : non tasser,2:tasser)
   // Vérifier si le tableau est existant
   if (!lafile)
      return ((int)-1); //! Erreur : le tableau n'existe pas
   if (est_sature_file(*lafile))
      return ((int)-4);              //! Erreur : fille est sature
   if (lafile->queue == maxelem - 1) //?si queue et dans la dernier element et n'est pas sature on va tasser
      tasser = tasser_file(lafile);
   lafile->queue++;
   lafile->tableau[lafile->queue] = valeur;
   return ((int)tasser); // Succès
}
// defiler : suppimer le debut (concept fifo first in first out)
int defiler_file(file *lafile)
{
   int ind; // Indice de parcours
   if (!lafile)
      return ((int)-1); //! Erreur : le tableau n'existe pas
   if (est_vide_file(*lafile))
      return ((int)-2); //! Erreur : le tableau est vide
   if (lafile->tete == lafile->queue)
      init_file(lafile);
   else lafile->tete++;

   return ((int)0); // Succès
}

// *********************************************************************************
void afficher_file(file lafile)
{
   int ind;
   for (ind = 0; ind < maxelem; ind++)
   {
      if (ind >= lafile.tete && ind <= lafile.queue)
         printf("|%d", lafile.tableau[ind]);
      else
         printf("| ");
   }
   printf("|   ");
   printf("tete: |%d|,queue: |%d|\n", lafile.tete, lafile.queue);
}
// *********************************************************************************

// ====== Menu pour les fonctions  ======
int menu()
{
   printf("\n\n\n===== MENU =====\n");
   printf("1. enfiler\n");
   printf("2. Afficher la file \n");
   printf("3. defiler\n");
   printf("4. nombre des element\n");
   printf("5. tester si la file est vide\n");
   printf("6. tester si la file est sature\n");
   printf("7. Quitter\n");
   printf("================\n");
   int choix;
   // en demande d'ecrire jusqu'au le nombre choisir est compris entre 1 et 8 (inclus 1 et 8)
   do
   {
      printf("Entrez votre choix: ");
      scanf("%d", &choix);
   } while (choix < 1 || choix > 7);
   return choix;
}

// === fonction des messages d'errors ===
void errors_message_file(int nombre)
{
   switch (nombre)
   {
   case -1:
      printf("Le tableau n'existe pas.\n");
      break;
   case -2:
      printf("Le tableau est vide.\n");
      break;
   case -3:
      printf("Indice invalide.\n");
      break;
   case -4:
      printf("Le tableau est sature.\n");
      break;

   default:
      printf("problem inconue\n");
      break;
   }
}
void exec(){
   int choix, valeur, resultat, indice;
   file *ptrFile = create_file();
   init_file(ptrFile);

   // === en repete de demander un nombre tanque leur est diff de 8 (quitter) ==
   do
   {
      choix = menu();
      switch (choix)
      {
      case 1: // enfiler
         printf("Entrez la valeur a inserer: ");
         scanf("%d", &valeur);
         resultat = enfiler_file(ptrFile, valeur);
         printf("\nresultat=%d", resultat);
         printf("\ntete=%d,queue=%d", ptrFile->tete, ptrFile->queue);
         if (resultat == 1)
            printf("la valeur %d est inserer avec success", valeur);

         else if (resultat == 2)
            printf("la valeur %d est inserer avec success apres un tassment", valeur);
         else
            errors_message_file(resultat);
         break;
      case 2: // affichage
         afficher_file(*ptrFile);
         break;
      case 3: // defiler
         resultat = defiler_file(ptrFile);
         if (resultat == 0)
         printf("Un élément a été retiré avec succès.\n");
         else
            errors_message_file(resultat);
         printf("\ntete=%d,queue=%d", ptrFile->tete, ptrFile->queue);
         break;
      case 4: // nombre des elements
         printf("le nombre d'element dans le tableau est : %d", nombre_elements_file(*ptrFile));
         break;
      case 5: // tester si vide
         resultat = est_vide_file(*ptrFile);
         if (resultat == 1)
            printf("la file est vide");
         else
            printf("la file non vide");
         break;
      case 6: // tester si vide
         resultat = est_sature_file(*ptrFile);
         if (resultat == 1)
            printf("la file est sature");
         else
            printf("la file non sature");
         break;
      }
   } while (choix != 7);
}
// === Main ===
int main()
{
   file *lafile = create_file();
   init_file(lafile);
   // tester la fonction taille
   printf("1. Taille initiale de la file: %d\n", nombre_elements_file(*lafile));
   // tester la fonction enfiler
   printf("2. Enfiler des elements 5, 10, 15 dans la file(tableau).\n");
   enfiler_file(lafile, 5);
   enfiler_file(lafile, 10);
   enfiler_file(lafile, 15);
   printf("Taille de la file apres enfiler: %d\n", nombre_elements_file(*lafile));
   printf("Contenu de la file: ");
   afficher_file(*lafile);

   // tester la fonction defiler
   printf("\n3. Defiler un element de la file.\n");
   defiler_file(lafile);
   printf("Taille de la file apres defiler: %d\n", nombre_elements_file(*lafile));
   printf("Contenu de la file: ");
   afficher_file(*lafile);

   // tester empliler jusqu'a saturer
   printf("\n4. Enfiler des elements jusqu'a arriver a  la fin du file.\n");
   for (int i = 0; i < 10; i++)
   {
      int res = enfiler_file(lafile, i * 10);
      if (res < 0)
      {
         errors_message_file(res);
         break;
      }
   }
   printf("Taille de la file apres enfiler: %d\n", nombre_elements_file(*lafile));
   printf("Contenu de la file: ");
   afficher_file(*lafile);

   //depiler encoure pour tster le tassment
   printf("\n5. Defiler deux elements de la file pour tester le tassment.\n");
   defiler_file(lafile);
   defiler_file(lafile);
   afficher_file(*lafile);

   printf("\n6. Enfiler un element pour tester le tassment.\n");
   enfiler_file(lafile, 999);
   afficher_file(*lafile);
   // libre la memoire
   free(lafile);
   return 0;
}