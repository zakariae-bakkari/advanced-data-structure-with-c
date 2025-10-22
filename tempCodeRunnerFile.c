{
      static int defilageCount = 0;
      int taille = tailleFile(file);
      for (int i = 0; i < taille; i++) {
         printf("Defilage %d: ", ++defilageCount);
         defiler(file);
         afficher_file(file);
      }
   }