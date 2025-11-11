#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct
{
    int tab[MAX];   /// tableau pour stocker les valeurs
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
    return (f.nb_elem == MAX);
}

/// Enfiler (ajouter un élément à la fin)
int enfiler_tfile(tfile* f, int val)
{
    if (!f) return -2;             /// file inexistante
    if (est_pleine_tfile(*f)) return 0;  /// file saturée

    f->queue = (f->queue + 1) % MAX;
    f->tab[f->queue] = val;
    f->nb_elem++;
    return 1;
}

/// Défiler (supprimer un élément de la tête)
int defiler_tfile(tfile* f)
{
    if (!f) return -2;
    if (est_vide_tfile(*f)) return -1;

    f->tete = (f->tete + 1) % MAX;
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
        int pos = (f.tete + i) % MAX;
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
        int pos = (f.tete + i) % MAX;
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
        int pos = (f->tete + i) % MAX;
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

/// Programme principal
int main()
{
    tfile* mafile = creer_tfile();

    printf("File vide ? %d\n", est_vide_tfile(*mafile));

    printf("\n--- Enfilage ---\n");
    enfiler_tfile(mafile, 1);
    enfiler_tfile(mafile, 2);
    enfiler_tfile(mafile, 4);
    afficher_tfile(*mafile);

    printf("\n--- Insertion en ordre ---\n");
    inserer_bonposition_tfile(mafile, 3);
    afficher_tfile(*mafile);

    printf("\n--- Défilage ---\n");
    defiler_tfile(mafile);
    afficher_tfile(*mafile);

    printf("\n--- Recherche ---\n");
    int val;
    printf("Entrer la valeur à chercher : ");
    scanf("%d", &val);
    if (recherche_tfile(*mafile, val))
        printf("Valeur trouvée !\n");
    else
        printf("Valeur non trouvée.\n");

    return 0;
}