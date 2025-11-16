#include "headers/header.h"
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
