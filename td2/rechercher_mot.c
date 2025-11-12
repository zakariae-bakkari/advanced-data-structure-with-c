#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxelem 50

int char_is (char car){
   if (('a' <= car) && (car <= 'z')){
      return 1;
   }
   else if (('A' <= car) && (car <= 'Z')){
      return 2;
   } 
}

char min_to_maj(char car){
   return (char)(car - 'a' + 'A');
}
char maj_to_min(char car){
   return (char)(car - 'A' + 'a');
}


void transformer_phrase(){
   char c;
   printf("Entrer une phrase: ");
   while ((c = getchar()) != '\n'){
      switch (char_is(c)){
         case 1:
            printf("%c", min_to_maj(c));
            break;
         case 2:
            printf("%c", maj_to_min(c));
            break;
         default:
            printf("%c", c);
            break;
      }
   }
}

char eliminer_espace(){
   char car;
   while ((car=getchar()) == ' ');// boucler tanque la valeur entrer c'est l'espace

   return ((char)car);
}
void rechercher_mot(){
   char motlu[maxelem],motrech[maxelem],car;
   int ind,cmpt=0;

   printf("\nentrer le mot a chercher :");
   scanf("%s",motrech);
   getchar();

   printf("\nenter la phrase : \n");

   do
   {
      //enter le caracter dans debut du phrase en elimniant les espaces
      car = eliminer_espace();
      ind =0;//pour contstruire le mo depuis depart
      while (car != ' ' && car != '\n')
      {
         motlu[ind++]=car;
         car = getchar();//les element suivant
      }

      // finiser le motlu
      motlu[ind]='\0';
      if (strcmp(motrech,motlu) == 0)
      {
         cmpt++;//incementer l'occurence du mot
      }
      
   } while (car != '\n');
   if (cmpt>0)
   {
      printf(" le mot %s est trove %d fois dans la phrase",motrech,cmpt);
   }
   else{
      printf(" le mot %s n'est pas trouve",motrech);
   }
   
}

int main(){
   // transformer_phrase();
   rechercher_mot();
   return 0;
}