#include <stdio.h>
#include <string.h>

int est_palindrome(char *str)
{
   int len = strlen(str);
   int ind = 0;
   for (ind = 0; ind < len/2; ind++)
   {
      if (str[ind] != str[len - ind - 1])
         return 0; // false
   }
   return 1; // true
}

int main()
{
   char str[100];

   printf("Entrez une chaine de caracteres: ");
   scanf("%s", str);

   if (est_palindrome(str))
      printf("La chaine \"%s\" est un palindrome.\n", str);
   else
      printf("La chaine \"%s\" n'est pas un palindrome.\n", str);

   return 0;
}