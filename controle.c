#include <stdio.h>
#define maxelem 10
// fonction 1 :
char minus_to_maj(char caractere)
{
   if (caractere >= 'a' && caractere <= 'z')
      return ((char)(caractere - 32));
   return ((char)caractere);
}

char maj_to_minus(char caractere)
{
   if (caractere >= 'A' && caractere <= 'Z')
      return ((char)(caractere + 32));
   return ((char)caractere);
}

char *car_to_tab(char caractere)
{
   if (caractere == '\t')
      return ((char *)"tab");
}
char *car_to_BLC(char caractere)
{
   if (caractere == ' ')
   {
      return ((char *)"BLC");
   }
}

// int trans_num(int num)
// {
//    if (num >= 0 && num <= 9)
//    {
//       return ((int)num < 5 ? num + 5 : num - 5);
//    }
//    return ((int)-1);
// }
// caractere : 0 -> 48 9 57
char trans_num(char num)
{
   if (num >= '0' && num <= '9')
   {
      return ((char)num < '5' ? num + 5 : num - 5);
   }
}

char *type_carac(char caractere)
{
   if (caractere >= '0' && caractere <= '9')
   {
      return "numerique";
   }
   else if (caractere >= 'a' && caractere <= 'z')
   {
      return "alpha minus";
   }
   else if (caractere >= 'A' && caractere <= 'Z')
   {
      return "alpha majus";
   }
   else if (caractere == '\t')
   {
      return "tabulation";
   }
   else if (caractere == ' ') // Fixed
   {
      return "blanc";
   }
   else
   {
      return "autre";
   }
}

void lit_clavier()
{
   char string[maxelem], string_formate[maxelem];
   int ind;
   printf("entrer une chaine de  caractere : ");
   scanf("%s", string);
   for (ind = 0; ind < maxelem; ind++)
   {
      char* type_string = type_carac(string[ind]);
      if (type_string == "numerique")
      {
         string_formate[ind] = trans_num(string[ind]);
      }
      else if (type_string == "alpha minus")
      {
         string_formate[ind] = minus_to_maj(string[ind]);
      }
      else if (type_string == "alpha majus")
      {
         string_formate[ind] = maj_to_minus(string[ind]);
      }
   }

   printf("%s",string_formate);
}
int main()
{
   lit_clavier();
}
