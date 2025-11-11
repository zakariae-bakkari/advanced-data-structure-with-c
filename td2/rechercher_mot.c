#include<stdio.h>
#include<stdlib.h>

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

int main(){
   transformer_phrase();
   return 0;
}