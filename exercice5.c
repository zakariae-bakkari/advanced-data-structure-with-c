#include <stdio.h>
#include <string.h>
#define max_taille 50

void lire_str(char mot[max_taille])
{
   printf("\nEntrer le mot : ");
   scanf("%s", mot);
}
int long_str(char mot[max_taille])
{
   int ind = 0;
   while (mot[ind] != '\0')
   {
      ind++;
   }
   return ind;
}

int comp_str(char mot[max_taille], char mot2[max_taille])
{
   int ind = 0;
   while (mot[ind] == mot2[ind])
      ind++;
   if (ind == 0)
      return -1;
   else if (ind - 1 == long_str(mot) && ind - 1 == long_str(mot2))
      return 0;
   return ind;
}

int recherche_mot(char mot[max_taille]) // o(n^2)
{
   char string[max_taille];
   printf("entrer votre phrase: ");
   scanf(" %[^\n]", string);
   printf("string : %s", string); // zakariae bakkari
   int ind = 0;                   // parcourir string
   int indj = 0;                  // parcourir motstring
   char motstring[max_taille];
   while (string[ind] != '\0') // o(n)
   {
      if (string[ind] != ' ')
      {
         motstring[indj] = string[ind]; // zakariae
         indj++;                        // indj = 8
      }
      else
      {
         motstring[indj] = '\0';            // zakariae \0
         if (comp_str(mot, motstring) == 0) // zakariae zakariae o(n)
            return 0;                       //
         indj = 0;
      }
      ind++;
   }

   return -1;
}
int main()
{
   char mot[max_taille];
   scanf("%s", mot);
   printf("\n%d", recherche_mot(mot));

   return 0;
}