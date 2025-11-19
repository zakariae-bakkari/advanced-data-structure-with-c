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
// Description : Verifie si la pile a atteint sa capacite maxelemimale (garde 1 case libre).
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


typedef struct {
    int tab[maxelem];
    int tete;   // indice du premier élément
    int queue;  // indice du dernier élément
    int nb_elem; // nombre d'éléments dans la liste
} tliste_circ;

/// Création
tliste_circ* creer_tliste_circ() {
    tliste_circ* pt = (tliste_circ*)malloc(sizeof(tliste_circ));
    if(!pt) {
        printf("Erreur d'allocation\n");
        exit(-1);
    }
    return pt;
}

/// Initialisation
int initialiser_tliste_circ(tliste_circ* latab) {
    if(!latab) {
        printf("Erreur d'allocation\n");
        exit(-1);
    }
    latab->tete = 0;
    latab->queue = -1;
    latab->nb_elem = 0;
    return 1;
}

/// Test si vide
int est_vide_tliste_circ(tliste_circ latab) {
    return (latab.nb_elem == 0);
}

/// Test si pleine
int est_pleine_tliste_circ(tliste_circ latab) {
    return (latab.nb_elem == maxelem);
}

/// Taille
int taille_tliste_circ(tliste_circ latab) {
    return latab.nb_elem;
}

/// Insertion à la fin
int inserer_fin_tliste_circ(tliste_circ* latab, int valeur) {
    if(!latab) return -1;
    if(est_pleine_tliste_circ(*latab)) return 0; // pleine

    latab->queue = (latab->queue + 1) % maxelem;
    latab->tab[latab->queue] = valeur;
    latab->nb_elem++;
    return 1;
}

/// Affichage
void afficher_tliste_circ(tliste_circ latab) {
    if(est_vide_tliste_circ(latab)) {
        printf("Liste vide\n");
        return;
    }

    int i = latab.tete;
    for(int cpt = 0; cpt < latab.nb_elem; cpt++) {
        printf("%d ", latab.tab[i]);
        i = (i + 1) % maxelem;
    }
    printf("\n");
}

/// Remplissage
int remplir_tliste_circ(tliste_circ* latab) {
    int entier, res;
    char reponse;
    if(!latab) return -1;
    do {
        printf("Entrer un entier : ");
        scanf("%d", &entier);
        res = inserer_fin_tliste_circ(latab, entier);
        if(!res) {
            printf("Tableau plein !\n");
            return -1;
        }
        printf("Voulez-vous ajouter un autre entier (O/N) : ");
        scanf(" %c", &reponse);
    } while(reponse == 'O' || reponse == 'o');
    return 1;
}

/// Suppression d'un élément à une position donnée
int supprimer_tliste_circ(tliste_circ* latab, int rang) {
    if(!latab) return -2;
    if(est_vide_tliste_circ(*latab)) return -1;
    if(rang < 0 || rang >= latab->nb_elem) return 0;

    ///int pos = (latab->tete + rang) % maxelem;

    for(int i = 0; i < latab->nb_elem - 1; i++) {
        int src = (latab->tete + i + 1) % maxelem;
        int dst = (latab->tete + i) % maxelem;
        if(i >= rang)
            latab->tab[dst] = latab->tab[src];
    }
    latab->queue = (latab->queue - 1 + maxelem) % maxelem;
    latab->nb_elem--;
    return 1;
}

/// Recherche d'une valeur
int recherche_tliste_circ(tliste_circ latab, int valeur) {
    int i = latab.tete;
    for(int cpt = 0; cpt < latab.nb_elem; cpt++) {
        if(latab.tab[i] == valeur)
            return 1;
        i = (i + 1) % maxelem;
    }
    return 0;
}

/// Insertion à un rang donné
int insertion_tliste_circ(tliste_circ* latab, int elem, int rang) {
    if(!latab) return -1;
    if(est_pleine_tliste_circ(*latab)) return 0;
    if(rang < 0 || rang > latab->nb_elem) return 0;

    // Calcul des indices circulaires
    int pos_insert = (latab->tete + rang) % maxelem;
    int pos_apres_queue = (latab->queue + 1) % maxelem;

    // Décalage vers la droite
    for(int i = latab->nb_elem; i > rang; i--) {
        int src = (latab->tete + i - 1) % maxelem;
        int dst = (latab->tete + i) % maxelem;
        latab->tab[dst] = latab->tab[src];
    }

    latab->tab[pos_insert] = elem;
    latab->queue = pos_apres_queue;
    latab->nb_elem++;
    return 1;
}



typedef struct
{
    int tab[maxelem];   /// tableau pour stocker les valeurs
    int tete;       /// indice de la tête
    int queue;      /// indice de la queue
    int nb_elem;    /// nombre d'éléments dans la file
} tfile;

/// Créer une file
tfile* creer_tfile()
{
    tfile* f = (tfile*)malloc(sizeof(tfile));
    if (!f)
    {
        printf("Erreur d'allocation mémoire\n");
        exit(-1);
    }
    f->tete = 0;
    f->queue = -1;
    f->nb_elem = 0;
    return f;
}

/// Vérifie si la file est vide
int est_vide_tfile(tfile f)
{
    return (f.nb_elem == 0);
}

/// Vérifie si la file est pleine
int est_pleine_tfile(tfile f)
{
    return (f.nb_elem == maxelem);
}

/// Enfiler (ajouter un élément à la fin)
int enfiler_tfile(tfile* f, int val)
{
    if (!f) return -2;             /// file inexistante
    if (est_pleine_tfile(*f)) return 0;  /// file saturée

    f->queue = (f->queue + 1) % maxelem;
    f->tab[f->queue] = val;
    f->nb_elem++;
    return 1;
}

/// Défiler (supprimer un élément de la tête)
int defiler_tfile(tfile* f)
{
    if (!f) return -2;
    if (est_vide_tfile(*f)) return -1;

    f->tete = (f->tete + 1) % maxelem;
    f->nb_elem--;
    return 1;
}

/// Afficher la file
void afficher_tfile(tfile f)
{
    if (est_vide_tfile(f))
    {
        printf("File vide.\n");
        return;
    }

    printf("Contenu de la file : ");
    for (int i = 0; i < f.nb_elem; i++)
    {
        int pos = (f.tete + i) % maxelem;
        printf("%d -> ", f.tab[pos]);
    }
    printf("NULL\n");
}

/// Remplir la file manuellement
int remplir_tfile(tfile* f)
{
    int val;
    char rep;
    if (!f) return -1;

    do
    {
        printf("Entrez une valeur : ");
        scanf("%d", &val);
        if (!enfiler_tfile(f, val))
        {
            printf("File pleine !\n");
            return 0;
        }
        printf("Ajouter un autre ? (o/n) : ");
        scanf(" %c", &rep);
    } while (rep == 'o' || rep == 'O');

    return 1;
}

/// Recherche d’un élément
int recherche_tfile(tfile f, int val)
{
    for (int i = 0; i < f.nb_elem; i++)
    {
        int pos = (f.tete + i) % maxelem;
        if (f.tab[pos] == val)
            return 1;
    }
    return 0;
}

/// Insertion d’un élément dans la bonne position (croissante)
int inserer_bonposition_tfile(tfile* f, int val)
{
    if (!f) return -2;
    if (est_pleine_tfile(*f)) return 0;

    /// Cas vide
    if (est_vide_tfile(*f))
    {
        enfiler_tfile(f, val);
        return 1;
    }

    /// File temporaire
    tfile temp;
    temp.tete = 0;
    temp.queue = -1;
    temp.nb_elem = 0;

    int insere = 0;
    for (int i = 0; i < f->nb_elem; i++)
    {
        int pos = (f->tete + i) % maxelem;
        int current = f->tab[pos];

        if (!insere && val < current)
        {
            enfiler_tfile(&temp, val);
            insere = 1;
        }
        enfiler_tfile(&temp, current);
    }

    if (!insere)
        enfiler_tfile(&temp, val);

    /// Copie de temp dans f
    *f = temp;
    return 1;
}
