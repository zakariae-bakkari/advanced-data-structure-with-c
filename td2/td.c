#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxlElem 20


char epurer_blan(){
   char car;
   while ((car=getchar()) == ' ');
   return car;
   
}


// Fonction : Chercher un mot dans un texte
// Entrée : aucune (saisie interactive)
// Sortie : aucune (affichage du résultat)
// Description : Compte le nombre d'occurrences d'un mot dans un texte saisi.
void chercher_mot(){
    char motCherche[maxlElem], motLu[maxlElem], charLu;
    int ind, cmpt = 0;
    
    printf("Entrez le mot a chercher (max %d caracteres) : ", maxlElem-1);
    scanf("%s", motCherche);
    
    printf("Entrez le texte dans lequel chercher le mot:\n");
    
    do {
        charLu = epurer_blan();  // lire + ignorer les espaces multiples
        ind = 0;
        // Lire un mot caractère par caractère
        while (charLu != ' ' && charLu != '\n' && ind < maxlElem - 1) {
            motLu[ind] = charLu;
            ind++;
            charLu = getchar();
        }
        
        motLu[ind] = '\0';  // Terminer la chaîne
        
        if (ind > 0 && strcmp(motLu, motCherche) == 0) {
            cmpt++;
        }
                
    } while (charLu != '\n');
    
    printf("Le mot '%s' a ete trouve %d fois dans le texte.\n", motCherche, cmpt);
}

// Fonction : Programme principal
// Entrée : aucune
// Sortie : 0 en fin d'exécution
// Description : Lance la recherche de mot dans un texte.
int main() {
   //  chercher_mot();
   char c,motLu[100];
   int ind = 0;
   while ((c=getchar()) != '\n')
   {
         motLu[ind]=c;
         ind++;
   }
   
   printf("Le mot lu est : %s\n",motLu);
    return ((int)0);
}