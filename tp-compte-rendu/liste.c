#include <stdio.h>
#include <stdlib.h>
#define max 10

typedef struct
{
    int tab[max];
    int tete;    // indice du premier élément
    int queue;   // indice du dernier élément
    int nb_elem; // nombre d'éléments dans la liste
} tliste_circ;

/// Création
tliste_circ *creer_tliste_circ()
{
    tliste_circ *pt = (tliste_circ *)malloc(sizeof(tliste_circ));
    if (!pt)
    {
        printf("Erreur d'allocation\n");
        exit(-1);
    }
    return pt;
}

/// Initialisation
int initialiser_tliste_circ(tliste_circ *latab)
{
    if (!latab)
    {
        printf("Erreur d'allocation\n");
        exit(-1);
    }
    latab->tete = 0;
    latab->queue = -1;
    latab->nb_elem = 0;
    return 1;
}

/// Test si vide
int est_vide_tliste_circ(tliste_circ latab)
{
    return (latab.nb_elem == 0);
}

/// Test si pleine
int est_pleine_tliste_circ(tliste_circ latab)
{
    return (latab.nb_elem == max);
}

/// Taille
int taille_tliste_circ(tliste_circ latab)
{
    return latab.nb_elem;
}

/// Insertion à la fin
int inserer_fin_tliste_circ(tliste_circ *latab, int valeur)
{
    if (!latab)
        return -1;
    if (est_pleine_tliste_circ(*latab))
        return 0; // pleine

    latab->queue = (latab->queue + 1) % max;
    latab->tab[latab->queue] = valeur;
    latab->nb_elem++;
    return 1;
}

/// Affichage
void afficher_tliste_circ(tliste_circ latab)
{
    if (est_vide_tliste_circ(latab))
    {
        printf("Liste vide\n");
        return;
    }

    int i = latab.tete;
    for (int cpt = 0; cpt < latab.nb_elem; cpt++)
    {
        printf("%d ", latab.tab[i]);
        i = (i + 1) % max;
    }
    printf("\n");
}

/// Remplissage
int remplir_tliste_circ(tliste_circ *latab)
{
    int entier, res;
    char reponse;
    if (!latab)
        return -1;
    do
    {
        printf("Entrer un entier : ");
        scanf("%d", &entier);
        res = inserer_fin_tliste_circ(latab, entier);
        if (!res)
        {
            printf("Tableau plein !\n");
            return -1;
        }
        printf("Voulez-vous ajouter un autre entier (O/N) : ");
        scanf(" %c", &reponse);
    } while (reponse == 'O' || reponse == 'o');
    return 1;
}

/// Suppression d'un élément à une position donnée
int supprimer_tliste_circ(tliste_circ *latab, int rang)
{
    if (!latab)
        return -2;
    if (est_vide_tliste_circ(*latab))
        return -1;
    if (rang < 0 || rang >= latab->nb_elem)
        return 0;

    /// int pos = (latab->tete + rang) % max;

    for (int i = 0; i < latab->nb_elem - 1; i++)
    {
        int src = (latab->tete + i + 1) % max;
        int dst = (latab->tete + i) % max;
        if (i >= rang)
            latab->tab[dst] = latab->tab[src];
    }
    latab->queue = (latab->queue - 1 + max) % max;
    latab->nb_elem--;
    return 1;
}

/// Recherche d'une valeur
int recherche_tliste_circ(tliste_circ latab, int valeur)
{
    int i = latab.tete;
    for (int cpt = 0; cpt < latab.nb_elem; cpt++)
    {
        if (latab.tab[i] == valeur)
            return 1;
        i = (i + 1) % max;
    }
    return 0;
}

/// Insertion à un rang donné
int insertion_tliste_circ(tliste_circ *latab, int elem, int rang)
{
    if (!latab)
        return -1;
    if (est_pleine_tliste_circ(*latab))
        return 0;
    if (rang < 0 || rang > latab->nb_elem)
        return 0;

    // Calcul des indices circulaires
    int pos_insert = (latab->tete + rang) % max;
    int pos_apres_queue = (latab->queue + 1) % max;

    // Décalage vers la droite
    for (int i = latab->nb_elem; i > rang; i--)
    {
        int src = (latab->tete + i - 1) % max;
        int dst = (latab->tete + i) % max;
        latab->tab[dst] = latab->tab[src];
    }

    latab->tab[pos_insert] = elem;
    latab->queue = pos_apres_queue;
    latab->nb_elem++;
    return 1;
}

/// Programme principal
int main()
{
    printf("\n\n========== Test de la liste avec tableau cerc ==========\n\n");
    tliste_circ *tabtest = creer_tliste_circ();
    initialiser_tliste_circ(tabtest);

    printf("Vide ? %d\n", est_vide_tliste_circ(*tabtest));
    printf("Taille : %d\n", taille_tliste_circ(*tabtest));

    inserer_fin_tliste_circ(tabtest, 5);
    afficher_tliste_circ(*tabtest);

    // remplir_tliste_circ(tabtest);
    printf("inserer des elements");
    inserer_fin_tliste_circ(tabtest, 10);
    inserer_fin_tliste_circ(tabtest, 20);
    inserer_fin_tliste_circ(tabtest, 30);
    inserer_fin_tliste_circ(tabtest, 40);
    inserer_fin_tliste_circ(tabtest, 50);
    afficher_tliste_circ(*tabtest);

    printf("\nSuppression du rang 2...\n");
    supprimer_tliste_circ(tabtest, 2);
    afficher_tliste_circ(*tabtest);

    int valeur;
    printf("\nEntrer une valeur à rechercher : ");
    scanf("%d", &valeur);
    if (recherche_tliste_circ(*tabtest, valeur))
        printf("Valeur trouvée\n");
    else
        printf("Valeur non trouvée\n");

    printf("\nInsertion de 8 au rang 3...\n");
    insertion_tliste_circ(tabtest, 8, 3);
    afficher_tliste_circ(*tabtest);
    printf("\n\n========== fin de test ==========\n\n");

    return 0;
}