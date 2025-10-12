#include <stdio.h>

int comparer_str(char mot1[100], char mot2[100])
{
   int ind = 0;
   while (mot1[ind] == mot2[ind] && mot1[ind] != '\0')
      ind++;
   if (mot1[ind] == '\0' && mot2[ind] == '\0')
      return 0;
   return 1;
}

int recherche(char phrase[100], char mot[100])
{
   printf("entrer la phrase:");
   scanf(" %[^\n]s", phrase);
   printf("entrer le mot:");
   scanf(" %s", mot);
   printf("%s %s", mot, phrase);
   char motphrase[100];
   int indi = 0, indj = 0;
   while (phrase[indi] != '\0') // la phrase n'a pas attiendre le fin du phrase
   {
      if (phrase[indi] != ' ')
      {
         motphrase[indj++] = phrase[indi]; // on stock le mot jusqua l'espace
      }
      else
      {
         motphrase[indj] = '\0';                // indiquer la fin du mot
         if (comparer_str(mot, motphrase) == 0) // comparer les deux
         {
            return 0;
         }
         indj = 0; // initialoser pour une nouveau mot
      }
      indi++;
   }
}
int main()
{
   char mot[100], phrase[100];
   int result = recherche(phrase, mot);
   if (result == 0)
      printf("le mot %s est trouve dans %s", mot, phrase);
   else
      printf("%s pas trouve", mot);
}