#include <stdio.h>
#include <stdlib.h>

/**
a - Fonction qui reçoit un caractère et indique son type.
**/
int char_is(char car)
{
   if (car == ' ')
      return -3; // espace
   if (car == '\t')
      return -2; // tabulation
   if (car == '\n')
      return -1; // retour chariot

   if (car >= '0' && car <= '9')
      return 0; // chiffre
   if (car >= 'a' && car <= 'z')
      return 1; // minuscule
   if (car >= 'A' && car <= 'Z')
      return 2; // majuscule

   return 99; // autre caractère
}

/**
b - Transformer le texte selon les règles données.
**/
void transformer_texte()
{
   char car;

   printf("\nEntrer un texte : \n");

   while ((car = getchar()) != '\n')
   {
      switch (char_is(car))
      {
      case 1: // minuscule
         printf("%c", 'z' - (car - 'a'));
         break;

      case 2: // majuscule
         printf("%c", 'Z' - (car - 'A'));
         break;

      case 0: // chiffre
         printf("%c", '9' - (car - '0'));
         break;

      case -3: // espace
         printf("BL");
         break;

      case -2: // tabulation
         printf("Tab");
         break;

      case -1: // retour chariot
         printf("RC");
         break;

      default:
         printf("%c", car);
      }
   }

   printf("RC\n");
}

int main()
{
   transformer_texte();
   return 0;
}

// un programme qui decale avec un nombre nb si nb =2 , a devien c b d e ... z a b
// si nb = -2 , a devien y z a b c ...
void transformer_texte_decale(int nb)
{
   char car;

   printf("\nEntrer un texte : \n");

   while ((car = getchar()) != '\n')
   {
      switch (char_is(car))
      {
      case 1: // minuscule
         printf("%c", (char)('z' + 'a' - car + nb));
         break;

      case 2: // majuscule
      printf("%c", (char)('Z' + 'A' - car + nb));
      break;

      default:
         printf("%c", car);
      }
   }

   printf("RC\n");
}
// si je fait z+a-car+2 (ex: z=122 , a=97 , car = z=122) 122+97-122+2 = 99 = c
//