#include <stdio.h>
#include <stdlib.h>

void image(unsigned char tabImage[255][255], short int resultas[256]) {
   int ind;
   //initialiser le tableau resultas a zero
   for (int ind = 0; ind < 256; ind++) {
      resultas[ind] = 0;
   }
   int ligne, colonne, valeurPixel;
   for (ligne = 0; ligne < 255; ligne++) {// parcourir les lignes
      for (colonne = 0; colonne < 255; colonne++) {// parcourir les colonnes
         valeurPixel = (unsigned char)tabImage[ligne][colonne];
         resultas[valeurPixel]++;
      }
   }
}

int main(){
   unsigned char tabImage[255][255];
   short int resultas[256];

   // Remplir le tableau tabImage avec des valeurs d'exemple
   for (int i = 0; i < 255; i++) {
      for (int j = 0; j < 255; j++) {
         tabImage[i][j] = (char)(rand() % 256); // Exemple de remplissage
      }
   }

   image(tabImage, resultas);

   // Afficher les resultats
   for (int i = 0; i < 256; i++) {
      if (resultas[i] > 0) {
         printf("Valeur du pixel %d: %d occurrences\n", i, resultas[i]);
      }
   }

   return 0;
}