#include<stdio.h>
#include<stdlib.h>


int type_caractaire(char car){
   if(car >= '0' && car <= '9'){
      return 1;
   }
   else if(car >= 'a' && car <= 'z'){
      return 2;
   }
   else if(car >= 'A' && car <= 'Z'){
      return 3;
   }
   else if (car == ' ')
   {
      return 4;
   }
   else if (car == '\t')
   {
      return 5;
   }
   else if (car == '\r')
   {
      return 6;
   }
   else{
      return 0;
   }
}


char trans_min(char car){
   return((char)('z'-car+'a'));
}

char trans_maj(char car){
   return((char)('Z'-car+'A'));
}

char trans_num(char car){
   return((char)('9'-car+'0'));
}

char* trans_tab(char car){
   return "tab";
}

char* trans_BL(char car){
   return "BL";
}

char* trans_RC(char car){
   return "RC";
}

void transformer(){
   char c;
   printf("Entrer un caractere: ");
   while ((c = getchar()) != '\n')
   {
      switch (type_caractaire(c))
      {
         case 1:
            printf("%c", trans_num(c));
            break;
         case 2:
            printf("%c", trans_min(c));
            break;
         case 3:
            printf("%c", trans_maj(c));
            break;
         case 4:
            printf("%s", trans_BL(c));
            break;
         case 5:
            printf("%s", trans_tab(c));
            break;
         case 6:
            printf("%s", trans_RC(c));
            break;
         default:
            printf("%c", c);
      }
   }
   
}

int main(){
   transformer();
   return 0;
}