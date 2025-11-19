#include <stdio.h>
#include <stdlib.h>

#define maxelem 10 // taille reelle du tableau (mais 1 case libre pour stockage temporaire)

// Definition de la pile
typedef struct {
    int tableau[maxelem];
    int sommet; // indice du sommet de la pile
    int sommet_temp; // indice temporaire pour l'affichage dans la case libre
} Pile;

// Fonction : Creer une nouvelle pile
// Entree : aucune
// Sortie : pointeur vers la pile creee ou NULL en cas d'erreur
// Description : Alloue dynamiquement la memoire pour une nouvelle pile.
Pile *create_tpile() {
    Pile *maPile = (Pile *)malloc(sizeof(Pile));
    // Tester l'allocation memoire
    if (!maPile) {
        printf("Erreur d'allocation memoire !\n");
        exit(0);
    }
    return ((Pile *)maPile);
}

// Fonction : Initialiser une pile
// Entree : pointeur sur une pile (Pile *maPile)
// Sortie : 1 en cas de succes, -1 si erreur
// Description : Initialise les indices sommet et sommet_temp de la pile.
int init_tpile(Pile *maPile) {
    // Test de l'existence de la pile
    if (!maPile)
        return ((int)-1);
    
    // Initialisation du sommet a -1 (pile vide)
    maPile->sommet = -1;
    // Initialisation du sommet temporaire (case libre pour affichage)
    maPile->sommet_temp = maxelem - 1;
    
    return ((int)1);
}

// Fonction : Verifier si la pile est vide
// Entree : pile (Pile maPile) passee par valeur
// Sortie : 1 si la pile est vide, 0 sinon
// Description : Teste si le sommet de la pile est a -1 (aucun element).
int est_vide_tpile(Pile maPile) {
    // Test si vide
    return ((int)(maPile.sommet == -1));// Retourne 1 si vide, 0 sinon
}

// Fonction : Verifier si la pile est saturee
// Entree : pile (Pile maPile) passee par valeur
// Sortie : 1 si la pile est saturee, 0 sinon
// Description : Verifie si la pile a atteint sa capacite maximale (garde 1 case libre).
int est_sature_tpile(Pile maPile) {
    // Test si saturee : on garde la case [maxelem-1] comme espace temporaire
    return ((int)(maPile.sommet == maxelem - 2));
}

// Fonction : Empiler un element dans la pile
// Entree : pointeur sur la pile (Pile *maPile), valeur a empiler (int valeur)
// Sortie : 1 en cas de succes, -1 si pile inexistante, -2 si pile saturee
// Description : Ajoute un element au sommet de la pile si elle n'est pas saturee.
int empiler_tpile(Pile *maPile, int valeur) {
    // Test de l'existence de la pile
    if (!maPile)
        return ((int)-1);

    // Test si saturee
    if (est_sature_tpile(*maPile))
        return ((int)-2);

    // Empiler l'element : incrementer le sommet et affecter la valeur
    maPile->tableau[++(maPile->sommet)] = valeur;
    
    return ((int)1); // Empilage avec succes
}

// Fonction : Depiler un element de la pile
// Entree : pointeur sur la pile (Pile *maPile)
// Sortie : 1 en cas de succes, -1 si pile inexistante, -3 si pile vide
// Description : Supprime l'element au sommet de la pile en decrementant l'indice.
int depiler_tpile(Pile *maPile) {
    // Test de l'existence de la pile
    if (!maPile)
        return ((int)-1);
    
    // Test si vide
    if (est_vide_tpile(*maPile))
        return ((int)-3);

    // Depiler l'element : decrementer le sommet
    (maPile->sommet)--;
    
    return ((int)1); // Depilage avec succes
}

// Fonction : Afficher le contenu de la pile
// Entree : pointeur sur la pile (Pile *maPile)
// Sortie : aucune (affichage console)
// Description : Affiche la pile en utilisant la case libre comme espace temporaire pour reconstruction.
void afficher_tpile(Pile *maPile) {
    int ind; // Declaration de la variable de boucle
    
    // Test de l'existence de la pile
    if (!maPile) {
        printf("Erreur d'allocation memoire: la pile n'existe pas !\n");
        return;
    }
    
    // Test si vide
    if (est_vide_tpile(*maPile)) {
        printf("Pile vide.\n");
        return;
    }

    printf("Affichage de la pile (du sommet vers la base) :\n");
    
    // Affichage et stockage temporaire dans la case libre
    for (ind = maPile->sommet; ind >= 0; ind--) {
        // Afficher les elements du sommet jusqu'a la base
        printf("pile[%d] = %d\n", ind, maPile->tableau[ind]);
        
        // Empiler temporairement dans la case libre
        maPile->tableau[maPile->sommet_temp] = maPile->tableau[ind];
        
        // Decrementer le sommet temporaire (sens inverse)
        maPile->sommet_temp--;
        
        // Decrementer le sommet
        maPile->sommet--;
    }
    
    // Reconstruction de la pile depuis la case libre
    printf("\nremettre les element depuis l'espace temporaire :\n");
    
    // Remettre les elements depuis l'espace temporaire
    for (ind = maPile->sommet_temp + 1 ; ind <= maxelem - 1; ind++) {
      maPile->tableau[++(maPile->sommet)] = maPile->tableau[ind];
      printf("Remise de l'element %d a la position %d\n", 
             maPile->tableau[ind], maPile->sommet);
      
  }

  // Restaurer l'état initial
  maPile->sommet_temp = maxelem - 1;
  
    
    printf("Pile reconstituee avec succes.\n\n");
}

// Fonction : Obtenir la taille de la pile
// Entree : pile (Pile maPile) passee par valeur
// Sortie : nombre d'elements dans la pile
// Description : Retourne le nombre actuel d'elements stockes dans la pile.
int taille_tpile(Pile maPile) {
    return ((int)(maPile.sommet + 1));
}

// Fonction : Rechercher un element dans la pile
// Entree : pile (Pile maPile) passee par valeur, valeur a rechercher (int valeur)
// Sortie : 1 si trouve, 0 sinon
// Description : Parcourt la pile pour chercher la valeur specifiee sans la modifier.
int rechercher_tpile(Pile maPile, int valeur) {
    int ind; // Declaration de la variable de boucle
    
    // Test si vide
    if (est_vide_tpile(maPile))
        return ((int)0);
    
    // Parcours de la pile
    for (ind = 0; ind <= maPile.sommet; ind++) {
        if (maPile.tableau[ind] == valeur)
            return ((int)1); // Trouve
    }
    
    return ((int)0); // Non trouve
}

// Fonction : Vider completement la pile
// Entree : pointeur sur la pile (Pile *maPile)
// Sortie : 1 en cas de succes, -1 si pile inexistante
// Description : Supprime tous les elements en remettant le sommet a -1.
int vider_tpile(Pile *maPile) {
    // Test de l'existence de la pile
    if (!maPile)
        return ((int)-1);
    
    // Remise a zero du sommet (pile vide)
    maPile->sommet = -1;
    // Reinitialisation du sommet temporaire
    maPile->sommet_temp = maxelem - 1;
    
    return ((int)1);
}

// Fonction : Programme principal de test
// Entree : aucune
// Sortie : 0 en fin d'execution
// Description : Teste toutes les fonctionnalites de la pile avec la methode de la case libre.
int main() {
    // === CREATION ET INITIALISATION ===
    printf("\n\n========== Test de la pile (methode de la case libre utilisee pour affichage) ==========\n\n");
    
    Pile *pile = create_tpile();
    int etat = init_tpile(pile);

    // Test de l'initialisation
    if (etat == -1) {
        printf("Erreur d'initialisation.\n");
        return ((int)-1);
    }

    printf("Pile creee et initialisee avec succes.\n");

    // === TEST SI PILE VIDE ===
    printf("\n1. Test si la pile est vide : ");
    if (est_vide_tpile(*pile))
        printf("Oui.\n");
    else
        printf("Non.\n");

    // === EMPILAGE D'ELEMENTS ===
    printf("\n2. Empiler les elements 5, 10, 15 :\n");
    printf("Resultat empilage 5 : %d\n", empiler_tpile(pile, 5));
    printf("Resultat empilage 10 : %d\n", empiler_tpile(pile, 10));
    printf("Resultat empilage 15 : %d\n", empiler_tpile(pile, 15));
    printf("Taille actuelle : %d\n", taille_tpile(*pile));

    // === AFFICHAGE DE LA PILE ===
    printf("\n3. Afficher la pile :\n");
    afficher_tpile(pile);
    afficher_tpile(pile);


    // === TEST DE RECHERCHE ===
   //  printf("\n3.5. Test de recherche (valeur 10) :\n");
   //  if (rechercher_tpile(*pile, 10))
   //      printf("Valeur 10 trouvee dans la pile.\n");
   //  else
   //      printf("Valeur 10 non trouvee dans la pile.\n");

    // === DEPILEMENT ===
    printf("\n4. Depiler un element :\n");
    printf("Resultat depilage : %d\n", depiler_tpile(pile));
    printf("Taille apres depilement : %d\n", taille_tpile(*pile));

    // === REAFFICHAGE APRÈS DEPILEMENT ===
    printf("\n5. Afficher la pile apres depilement :\n");
    afficher_tpile(pile);

    // === EMPILAGE JUSQU'À SATURATION ===
    printf("\n6. Empiler jusqu'a saturation :\n");
    while (!est_sature_tpile(*pile)) {
        int valeur = (pile->sommet + 2) * 10;
        printf("Empilage de %d : %d\n", valeur, empiler_tpile(pile, valeur));
    }
    printf("Pile saturee a %d elements (1 case libre conservee).\n", taille_tpile(*pile));

    // === AFFICHAGE DE LA PILE SATUREE ===
    printf("\n7. Afficher la pile saturee :\n");
    afficher_tpile(pile);

    // === TEST DE VIDAGE ===
   //  printf("\n8. Test de vidage de la pile :\n");
   //  printf("Resultat vidage : %d\n", vider_tpile(pile));
   //  printf("Taille apres vidage : %d\n", taille_tpile(*pile));
   //  printf("Test si vide apres vidage : %s\n", est_vide_tpile(*pile) ? "Oui" : "Non");

    // === LIBERATION DE LA MEMOIRE ===
    free(pile);
    printf("\n========== Fin du test ==========\n\n");

    return ((int)0);
}