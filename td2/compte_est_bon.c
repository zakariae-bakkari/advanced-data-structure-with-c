#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.00001  // Pour la comparaison de flottants

// Fonction : Comparer deux flottants avec tolérance
int sont_egaux(float a, float b) {
    return ((int)(fabs(a - b) < EPSILON));
}

// Fonction : Tester une combinaison d'opérations
float tester_combinaison(float combinaison[3], char operations[4], float cible) {
    float resultat;
    float trouve = 0;
    int opt, opt2;  // Déclaration des variables de boucle
    
    for (opt = 0; opt < 4; opt++) {
        for (opt2 = 0; opt2 < 4; opt2++) {
            // ✅ CORRECTION : Calculer avec priorité des opérations
            
            // Cas 1 : Si deuxième opération est * ou /, la faire d'abord
            if (operations[opt2] == '*' || operations[opt2] == '/') {
                float temp;
                
                // Vérification division par zéro
                if (operations[opt2] == '/' && combinaison[2] == 0) {
                    continue;  // Passer à l'itération suivante
                }
                
                // Calculer d'abord combinaison[1] op2 combinaison[2]
                if (operations[opt2] == '*') {
                    temp = combinaison[1] * combinaison[2];
                } else {
                    temp = combinaison[1] / combinaison[2];
                }
                
                // Puis combinaison[0] op1 temp
                resultat = combinaison[0];
                switch (operations[opt]) {
                    case '+':
                        resultat += temp;
                        break;
                    case '-':
                        resultat -= temp;
                        break;
                    case '*':
                        resultat *= temp;
                        break;
                    case '/':
                        if (temp == 0) continue;  // Éviter division par zéro
                        resultat /= temp;
                        break;
                }
            } 
            // Cas 2 : Sinon, calculer de gauche à droite
            else {
                resultat = combinaison[0];
                
                // Première opération
                switch (operations[opt]) {
                    case '+':
                        resultat += combinaison[1];
                        break;
                    case '-':
                        resultat -= combinaison[1];
                        break;
                    case '*':
                        resultat *= combinaison[1];
                        break;
                    case '/':
                        if (combinaison[1] == 0) continue;  // Éviter division par zéro
                        resultat /= combinaison[1];
                        break;
                }
                
                // Deuxième opération
                switch (operations[opt2]) {
                    case '+':
                        resultat += combinaison[2];
                        break;
                    case '-':
                        resultat -= combinaison[2];
                        break;
                    case '*':
                        resultat *= combinaison[2];
                        break;
                    case '/':
                        if (combinaison[2] == 0) continue;  // Éviter division par zéro
                        resultat /= combinaison[2];
                        break;
                }
            }
            
            // ✅ CORRECTION : Comparaison de flottants avec tolérance
            if (sont_egaux(resultat, cible)) {
                printf("Solution: %.2f %c %.2f %c %.2f = %.2f\n", 
                       combinaison[0], operations[opt], combinaison[1], 
                       operations[opt2], combinaison[2], resultat);
                trouve++;
            }
        }
    }
    return ((float)trouve);
}

// Fonction : Permuter deux éléments
void echanger(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction : Générer toutes les permutations et tester
float resoudre_compte_est_bon(float nombres[3], char operations[4], float cible) {
    float total_solutions = 0;
    int permutations[6][3] = {
        {0, 1, 2}, {0, 2, 1}, {1, 0, 2},
        {1, 2, 0}, {2, 0, 1}, {2, 1, 0}
    };
    int ind, j;  // Variables de boucle
    
    printf("Recherche de solutions pour atteindre %.2f avec [%.2f, %.2f, %.2f]:\n\n", 
           cible, nombres[0], nombres[1], nombres[2]);
    
    for (ind = 0; ind < 6; ind++) {
        float combinaison[3];
        
        // Créer la permutation
        for (j = 0; j < 3; j++) {
            combinaison[j] = nombres[permutations[ind][j]];
        }
        
        printf("--- Permutation [%.2f, %.2f, %.2f] ---\n", 
               combinaison[0], combinaison[1], combinaison[2]);
        
        float solutions = tester_combinaison(combinaison, operations, cible);
        total_solutions += solutions;
        
        if (solutions == 0) {
            printf("Aucune solution trouvée.\n");
        }
        printf("\n");
    }
    
    return ((float)total_solutions);
}

// Fonction : Programme principal
// Entrée : aucune
// Sortie : 0 en fin d'exécution
// Description : Interface utilisateur pour le jeu "le compte est bon".
int main() {
    printf("========= Le Compte Est Bon (Version Corrigée) ==========\n");
    
    float nombres[3];
    float cible;
    char operations[4] = {'+', '-', '*', '/'};
    
    // Saisie des nombres
    printf("Entrez les 3 nombres:\n");
    printf("Nombre 1: ");
    scanf("%f", &nombres[0]);
    printf("Nombre 2: ");
    scanf("%f", &nombres[1]);
    printf("Nombre 3: ");
    scanf("%f", &nombres[2]);
    
    // Saisie de la cible
    printf("Entrez la cible: ");
    scanf("%f", &cible);
    
    // Résolution
    float total = resoudre_compte_est_bon(nombres, operations, cible);
    
    if (total == 0) {
        printf("❌ Aucune solution trouvée pour atteindre %.2f\n", cible);
    } else {
        printf("✅ Total: %.0f solution(s) trouvée(s) !\n", total);
    }
    
    return ((int)0);
}