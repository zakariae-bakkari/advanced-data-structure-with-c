#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
bool contenant_un_zero(int nombre)
{
   while (nombre != 0)
   {
      if (nombre % 10 == 0)
         return true;
      nombre = nombre / 10;
   }
   return false;
}
float somme_elements(int nombre)
{
   float somme = 0;
   int ind;
   for (ind = 1; ind <= nombre; ind++)
      if (!contenant_un_zero(ind)) 
         somme += (float)1 / ind;
   return (float)somme;
}
int main()
{
   int nombre;
   printf("Entrez un nombre: ");
   scanf("%d", &nombre);
   printf("La somme des inverses des entiers de 1 a %d (excluant les multiples de 10) est: %f\n", nombre, somme_elements(nombre));
   return 0;
}