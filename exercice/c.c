#include <stdio.h>
#define TAILLE 100

int main(){

   int tab[TAILLE];//78-9 ->8-9-9
   int rang =5, ind=7,sup;
   for (int courant = rang; courant < ind; courant++)
   {
      tab[courant] = tab[courant + 1];//i1: tab[5]=tab[6], tab[6]=tab[7]
   }
   ind --;
   
}