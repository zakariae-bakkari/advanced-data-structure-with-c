#include "header.h"

// === Main ===
int main()
{
   Tfile *laTfile = create_Tfile();
   init_Tfile(laTfile);
   printf("\n\n========== Test des fonctions de la Tfile (tableau) ==========\n\n");
   if (!laTfile)
   {
      printf("Erreur d'allocation memoire\n\n");
      return -1;
   }else
      printf("La Tfile est cree avec success\n\n");
   
   // tester la fonction taille
   printf("1. Taille initiale de la Tfile: %d\n\n", nombre_elements_Tfile(*laTfile));
   // tester la fonction enTfiler
   printf("2. EnTfiler des elements 5, 10, 15 dans la Tfile(tableau).\n\n");
   enTfiler_Tfile(laTfile, 5);
   enTfiler_Tfile(laTfile, 10);
   enTfiler_Tfile(laTfile, 15);
   printf("Taille de la Tfile apres enTfiler: %d\n", nombre_elements_Tfile(*laTfile));
   printf("Contenu de la Tfile: ");
   afficher_Tfile(*laTfile);

   // tester la fonction deTfiler
   printf("\n3. DeTfiler un element de la Tfile.\n\n");
   deTfiler_Tfile(laTfile);
   printf("Taille de la Tfile apres deTfiler: %d\n", nombre_elements_Tfile(*laTfile));
   printf("Contenu de la Tfile: ");
   afficher_Tfile(*laTfile);

   // tester empliler jusqu'a saturer
   printf("\n4. EnTfiler des elements jusqu'a arriver a  la fin du Tfile.\n\n");
   for (int i = 0; i < 10; i++)
   {
      int res = enTfiler_Tfile(laTfile, i * 10);
      if (res < 0)
      {
         printf("*la Tfile devenir saturee.*\n");
         break;
      }
   }
   printf("Taille de la Tfile apres enTfiler: %d\n", nombre_elements_Tfile(*laTfile));
   printf("Contenu de la Tfile: ");
   afficher_Tfile(*laTfile);

   //depiler encoure pour tster le tassment
   printf("\n5. DeTfiler deux elements de la Tfile pour tester le tassment.\n\n");
   deTfiler_Tfile(laTfile);
   deTfiler_Tfile(laTfile);
   afficher_Tfile(*laTfile);

   printf("\n6. EnTfiler un element pour tester le tassment.\n\n");
   enTfiler_Tfile(laTfile, 999);
   afficher_Tfile(*laTfile);
   // libre la memoire
   free(laTfile);
   printf("\n\n========== Fin des tests ==========\n\n");
   return 0;
}