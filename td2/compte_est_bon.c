/*//!### II Le compte est bon
//*Le but du jeu "le compte est bon" est de déterminer la combinaison des opérations arithmétiques ($(+, -, *, /)$) à appliquer sur trois nombres pour obtenir une cible donnés $S$ À défaut d'obtenir $S$, il faut déterminer le nombre le plus proche de la cible choisie $S$

par exemple ona 3 nombre (10 4 6)  et s=12 -> 10 - 4 + 6

*/

#include <stdio.h>

float tester_combinaison(float combinaison[3], char operations[4], float cible)
{
   // tester les 16 possiblite
   float resultas;
   float trouve = 0;
   for (int opt = 0; opt < 4; opt++)
   {
      for (int opt2 = 0; opt2 < 4; opt2++)
      {
         resultas = combinaison[0]; // commence par le premier element
         // ajouter l'operation 1 avec l'element 2
         switch (operations[opt])
         {
         case '+':
            resultas += combinaison[1];
            break;
         case '-':
            resultas -= combinaison[1];
            break;
         case '*':
            resultas *= combinaison[1];
            break;
         case '/':
            resultas /= combinaison[1];
            break;
         }

         // ajouter l'operation 2 avec l'element 3
         switch (operations[opt2])
         {
         case '+':
            resultas += combinaison[2];
            break;
         case '-':
            resultas -= combinaison[2];
            break;
         case '*':
            resultas *= combinaison[2];
            break;
         case '/':
            resultas /= combinaison[2];
            break;
         }

         // ici le resultas sera comme cela resulta = combinaison[0] operation1 combinaison[1] operation2 combinaison[2]
         if (resultas == cible)
         {
            printf("cible = %.2f%c%.2f%c%.2f \n", combinaison[0], operations[opt], combinaison[1], operations[opt2], combinaison[2]);
            trouve++;
         }
      }
   }
   return ((float)trouve);
}
int main()
{
   printf("========= Programme qui trouve la combinaison de 3 nombres (1,2,3) pour atteindre une cible ==========\n");
   float combinaison[3] = {1, 2, 3}, cible;
   char operations[4] = {'+', '-', '*', '/'};
   printf("Entrer une cible: ");
   scanf("%f", &cible);
   if (tester_combinaison(combinaison, operations, cible) == 0)
   {
      printf("cible n'a pas atteindre");
   }
}
