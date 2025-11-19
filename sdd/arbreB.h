#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#ifndef ARBREB_H
#define ARBREB_H

typedef struct noeud {
    int valeur;
    struct noeud* gauche;
    struct noeud* droite;
} Noeud;

typedef struct Noeud ArbreBinaire;/// Alias pour un arbre binaire

// Fonction pour créer un nouveau nœud
Noeud* creerNoeud(int valeur) {
    Noeud* nouveauNoeud = (Noeud*)malloc(sizeof(Noeud));
    if (!nouveauNoeud) {
        printf("Erreur d'allocation mémoire\n");
        exit(-1);
    }
    nouveauNoeud->valeur = valeur;
    nouveauNoeud->gauche = NULL;
    nouveauNoeud->droite = NULL;
    return ((Noeud*)nouveauNoeud);
}

// Fonction d'insertion dans l'arbre binaire 

#endif