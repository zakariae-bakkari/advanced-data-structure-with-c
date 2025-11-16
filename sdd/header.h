#ifndef POINTEUR_FILE_COMPLETE_H
#define POINTEUR_FILE_COMPLETE_H

#include <stdio.h>
#include <stdlib.h>

// structure d'une cellule qui divise en deux partie (valeur pointeur)
typedef struct cel
{
   int valeur;          //  valeur de la cellule
   struct cel *suivant; // un pointeur qui point sur l'element suivant
} cellule;

//* ================================ File avec pointeurs =============================== //* //

// structure d'une file qui contient  deux pointeur (tete et queue) : concept FIFO
typedef struct File
{
   cellule *tete;
   cellule *queue;
} File;

// creation d'un cellule
static inline cellule *creeCellule(int valeur)
{
   cellule *cel = (cellule *)malloc(sizeof(cellule));
   if (!cel)
      return NULL;
   cel->valeur = valeur;
   cel->suivant = NULL;
   return ((cellule *)cel);
}

// alocation d'une file et l'initialisation des pointeur
static inline File *init_file()
{
   File *file = (File *)malloc(sizeof(File));
   if (!file)
   {
      printf("Erreur d'allocation memoire");
      return (NULL);
   }
   file->tete = NULL;  // initialiser la tete a null
   file->queue = NULL; // initialiser la queue a null
   return ((File *)file);
}

// tester si la file est vide
static inline int est_vide_file(File *file)
{

   return ((int)(!file->tete && !file->queue)); // une seul est sufisante
}

// returner la taille d'un fille en parcourant du tete jusqua  la fin (null)
static inline int tailleFile(File *file) // pas correct car il na pas utilise le principe fifo
{
   if (est_vide_file(file))
      return 0;
   cellule *temp = file->tete;
   int taille = 0;
   while (temp != NULL)
   {
      taille++;
      temp = temp->suivant;
   }
   return taille;
}

// fonction recursive pour calculer la taille de la file
static inline int taille_recursive_file(cellule *cel)
{
   if (cel == NULL)
      return ((int)0);
   return 1 + taille_recursive_file(cel->suivant);
}

// enfiler la file : ajouter au dernier
static inline int enfiler(File *file, int valeur)
{
   // verifer l'allocation de la file
   if (!file)
   {
      printf("la file n'exist pas (pas allouer) \n");
      return ((int)-1);
   }
   cellule *nouvelleCellule = creeCellule(valeur);

   // verifer l'allocation de la nouvelle cellule
   if (!nouvelleCellule)
   {
      printf("Erreur d'allocation memoire pour la nouvelle cellule \n");
      return ((int)-2); // Error d'allocation
   }

   // si la file est vide
   if (est_vide_file(file))
   {
      file->tete = file->queue = nouvelleCellule; // la tete et la queue point sur la nouvelle cellule
   }
   else
   {
      file->queue->suivant = nouvelleCellule; // l'element suivant de la queue pointe sur la nouvelle cellule
      file->queue = nouvelleCellule;          // la queue pointe sur la nouvelle cellule
   }
   return ((int)1); // succes
}

// fonction pour defiler la file : supprimer du debut
static inline int defiler(File *file)
{
   // verifer l'allocation de la file
   if (!file)
   {
      printf("la file n'exist pas (pas allouer) \n");
      return ((int)-1); // Error d'allocation
   }

   // verifer si la file est vide
   if (est_vide_file(file))
   {
      printf("la file est vide \n");
      return ((int)-2); // Error file vide
   }

   // defiler l'element du tete en resurvant l'adresse de la cellule a supprimer
   cellule *cellule_a_supprimer = file->tete; // sauvegarder l'adresse de la tete
   file->tete = file->tete->suivant;

   // reset the queue if the tete is null
   if (file->tete == NULL)
   {
      file->queue = NULL;
   }

   free(cellule_a_supprimer); // liberer la memoire de la cellule supprimer
   return ((int)1);           // succes
}

// insertion a bonne place dans la file
static inline void inserer_bonne_place_file(File *file, int valeur)
{
   File *temp = init_file();
   if (!file)
   {
      printf("la file n'exist pas (pas allouer) \n");
      return;
   }

   // Cas 1: File vide
   if (est_vide_file(file))
   {
      enfiler(file, valeur);
      free(temp);
      return;
   }

   // Cas 2: Insertion au debut
   if (valeur < file->tete->valeur)
   {
      cellule *NE = creeCellule(valeur);
      if (NE)
      {
         NE->suivant = file->tete;
         file->tete = NE;
      }
      free(temp);
      return;
   }

   // Cas 3: Insertion a la fin
   if (valeur >= file->queue->valeur)
   {
      enfiler(file, valeur);
      free(temp);
      return;
   }

   // Cas 4: Insertion au milieu
   // Défiler jusqu'à trouver la bonne place
   while (!est_vide_file(file) && file->tete->valeur < valeur)
   {
      enfiler(temp, file->tete->valeur);
      defiler(file);
   }

   // Insérer la nouvelle valeur
   enfiler(temp, valeur);

   // Transférer le reste
   while (!est_vide_file(file))
   {
      enfiler(temp, file->tete->valeur);
      defiler(file);
   }

   // Remettre tout dans la file originale
   while (!est_vide_file(temp))
   {
      enfiler(file, temp->tete->valeur);
      defiler(temp);
   }

   // Libérer la file temporaire
   free(temp);
}

// tris de la file en utilisant l'insertion a bonne place
static inline void trier_file(File *file)
{
   File *temp = init_file();
   if (!file)
   {
      printf("la file n'exist pas (pas allouer) \n");
      return;
   }

   while (!est_vide_file(file))
   {
      int valeur = file->tete->valeur;
      defiler(file);
      inserer_bonne_place_file(temp, valeur);
   }

   // Remettre tout dans la file originale
   while (!est_vide_file(temp))
   {
      enfiler(file, temp->tete->valeur);
      defiler(temp);
   }

   // Libérer la file temporaire
   free(temp);
}

static inline void supprimer_doublon(File *file)
{
   cellule *crt;
   File *temp = init_file();
   File *res = init_file();
   if (!file)
      return;
   if (est_vide_file(file))
      return;

   while (!est_vide_file(file))
   {
      crt = file->tete;
      file->tete = crt->suivant;
      crt->suivant = NULL;
      res->queue->suivant = crt;
      res->queue = crt;
      while (!est_vide_file(file))
      {
         crt = file->tete;
         if (crt->valeur != res->tete->valeur)
         {
            /* code */
         }
      }
   }
}

// fonction recherche recursive dans la file
static inline int recherche_recursive_file_2(cellule *cel, int valeur, int position)
{
   if (cel == NULL)
      return ((int)0); // valeur non trouvee
   if (cel->valeur == valeur)
      return (position); // valeur trouvee
   return recherche_recursive_file_2(cel->suivant, valeur, position + 1);
}
static inline int recherche_recursive_file(File *file, int valeur)
{
   return recherche_recursive_file_2(file->tete, valeur, 1);
}
// affichier en utilsant une copie de la file
static inline void afficher(File *file)
{
   if (est_vide_file(file))
   {
      printf("File vide\n");
      return;
   }

   cellule *temp = file->tete;
   while (temp != NULL)
   {
      printf("%d->", temp->valeur);
      temp = temp->suivant;
   }
   printf("NULL\n");
}

// afficher les details de la file
static inline void afficher_file(File *file)
{
   cellule *courant = file->tete;
   printf("Affichage : ");
   printf("Tete-> ");
   while (courant != NULL)
   {
      printf("%d-> ", courant->valeur);
      courant = courant->suivant;
   }
   printf("NULL\n");
   printf("Tete: ");
   if (file->tete != NULL)
   {
      printf("%d\n", file->tete->valeur);
   }
   else
   {
      printf("NULL\n");
   }
   printf("Queue: ");
   if (file->queue != NULL)
   {
      printf("%d\n", file->queue->valeur);
   }
   else
   {
      printf("NULL\n");
   }
   printf("\n");
}

//* ================================ liste avec pointeurs =============================== //* //
typedef cellule liste;

cellule *init_null()
{
   return ((cellule *)NULL);
}

cellule *createcellule(int valeur)
{
   cellule *cel = (cellule *)malloc(sizeof(cellule));
   if (!cel)
      return NULL;
   cel->valeur = valeur;
   cel->suivant = NULL;
   return ((cellule *)cel);
}
// tester si la liste est vide
int est_vide_liste(liste *maliste)
{
   return ((int)(maliste == NULL));
};

// insertion a une position
liste *inserer_liste(liste *maliste, int valeur, int position) // complexite O(n)
{
   liste *nouveau_element, *courant;
   int compteur = 1;
   if (position < 1) // la position allon de 1 jusqua ...
   {
      return ((liste *)maliste);
   }

   // si le premier
   if (position == 1)
   {
      nouveau_element = createcellule(valeur);
      nouveau_element->suivant = maliste;
      return ((liste *)nouveau_element);
   }

   // si position > 1
   courant = maliste;
   while (((compteur + 1) != position) && (courant->suivant))
   {
      courant = courant->suivant;
      ++compteur;
   }
   // si position est valide
   if ((compteur + 1) == position)
   {
      nouveau_element = (liste *)createcellule(valeur);
      nouveau_element->suivant = courant->suivant;
      courant->suivant = nouveau_element;
      return ((liste *)maliste); // returner la tete du liste
   }
   // on n'utilise pas else car ona deja fair return !!!!
   printf("la position est invalid");
   return ((liste *)maliste);
}

// supprimer une position donnes
liste *supprimer(liste *maliste, int position)
{
   liste *courant = maliste;
   int conteur = 1;
   if (est_vide_liste(maliste))
   {
      printf("la liste est vide");
      return ((liste *)maliste);
   }
   if (position == 1)
   {
      liste *celleul_a_supprimer = maliste;
      maliste = maliste->suivant;
      free(celleul_a_supprimer);
      return maliste;
   }

   while (((conteur + 1) < position) && (courant->suivant))
   {
      courant = courant->suivant;
      conteur++;
   }
   if (conteur + 1 == position)
   {
      liste *cellule_a_supprimer = courant->suivant;
      courant->suivant = courant->suivant->suivant;
      free(cellule_a_supprimer);

      return maliste;
   }
   printf("Position invalide\n");
   return maliste;
}
// supprimer la premier occurence d'une valeur
liste *supprimer_prem_occu(liste *maliste, int valeur)
{
   liste *courant = maliste;
   // le cas 1 : la liste est vide
   if (est_vide_liste(maliste))
   {
      printf("la liste est vide");
      return ((liste *)maliste);
   }

   // le cas 2 : l'element est trouve au debut
   if (maliste->valeur == valeur)
   {
      liste *cellule_a_supprimer = maliste;
      maliste = maliste->suivant;
      free(cellule_a_supprimer);
      return ((liste *)maliste);
   }

   // le cas 3 : l'element est trouve au mileu ou a la fin
   // tanque le courant est n'est pas null et lla valeur du suivant et deffer de la valeur a supprimer
   while (courant->suivant != NULL && courant->suivant->valeur != valeur)
   {
      courant = courant->suivant;
   }
   // verifier si l'element a ete trouve si courant ->suivant est egal null donc est n'ap pas ....
   if (courant->suivant != NULL)
   {
      liste *cellule_a_supprimer = courant->suivant;
      courant->suivant = cellule_a_supprimer->suivant;
      free(cellule_a_supprimer);
      printf("Valeur %d supprimee avec success\n", valeur);
      return ((liste *)maliste);
   }

   printf("la valeur %d pas trouvee\n", valeur);
   return ((liste *)maliste);
}

// supprimer  tout les occurence d'une valeur
liste *supprimer_tout_occu(liste *maliste, int valeur)
{
   liste *courant;
   int trouve = 0;
   // le cas 1 : la liste est vide
   if (est_vide_liste(maliste))
   {
      printf("la liste est vide");
      return ((liste *)maliste);
   }

   // le cas 2 : l'element est trouve au debut
   while (maliste != NULL && maliste->valeur == valeur)
   {
      liste *cellule_a_supprimer = maliste;
      maliste = maliste->suivant;
      free(cellule_a_supprimer);
      printf("Valeur %d supprimee du debut\n", valeur);
      trouve++;
   }
   // le cas 3 : l'element est trouve au mileu ou a la fin
   // en parcour touts la liste
   courant = maliste;
   while (courant->suivant != NULL)
   {
      if (courant->suivant->valeur == valeur)
      {
         liste *cellule_a_supprimer = courant->suivant;
         courant->suivant = cellule_a_supprimer->suivant;
         free(cellule_a_supprimer);
         printf("Valeur %d supprimee avec success\n", valeur);
         trouve++;
      }
      else // en passe au suivant si ne supprime pas
      {
         courant = courant->suivant;
      }
   }
   if (trouve == 0)
      printf("la valeur %d n'est pas trouve dans la liste \n", valeur);
   else
      printf("la valeur %d a ete trouve %d fois (on les supprimer)\n", valeur, trouve);

   return ((liste *)maliste);
}

// modifier valeur d'un position
liste *modifier_liste(liste *maliste, int position, int new_valeur)
{
   liste *courant = maliste;
   int conteur = 1; // le conteur debut avec 1 (position 1)
   // cas 1 : si la liste est vide (null)
   if (est_vide_liste(maliste))
   {
      printf("la liste est vide pas de valeurs");
      return ((liste *)maliste);
   }

   // cas 2 :
   while ((conteur != position) && (courant->suivant != NULL))
   {
      conteur++;
      courant = courant->suivant;
   }
   if (conteur == position)
   {
      courant->valeur = new_valeur;
      return ((liste *)maliste);
   };
   printf("la prosition est invalide!!!\n");
   return ((liste *)maliste);
}

// modifier la valeur de touts les valeurs chercher val
liste *modifier_liste_touts_valeur(liste *maliste, int valeur, int valeur_a_change)
{
   liste *courant = maliste;
   int modifications = 0;

   // cas 1 : si la liste est vide (null)
   if (est_vide_liste(maliste))
   {
      printf("la liste est vide pas de valeurs");
      return ((liste *)maliste);
   }

   // cas 2 :
   while (courant != NULL)
   {
      if (courant->valeur == valeur_a_change)
      {
         courant->valeur = valeur;
         modifications++;
         printf("Valeur %d modifiee en %d a la position %d \n", valeur_a_change, valeur, modifications);
      };
      courant = courant->suivant;
   }

   // printf("la prosition est invalide!!!\n");
   return ((liste *)maliste);
}
int taille_liste_recursive(liste *maliste)
{
   if (maliste == NULL)
      return 0;
   return 1 + taille_liste_recursive(maliste->suivant);
}

liste *inserer_bonne_place_pliste(liste *maliste, int valeur)
{
   liste *NE, *crt;
   NE = (liste *)createcellule(valeur);

   // existance de la liste (vide)
   if (est_vide_liste(maliste))
      return ((liste *)NE);

   // insertion au debut
   if (maliste->valeur >= valeur)
   {
      NE->suivant = maliste;
      return ((liste *)NE);
   }

   // insertion au milieu ou a la fin
   crt = maliste;
   while (crt->suivant)
   {
      if (NE->valeur <= crt->suivant->valeur)
      {
         NE->suivant = crt->suivant;
         // crt->suivant = NE;
         // return ((liste*) maliste);
         break;
      }
      crt = crt->suivant;
   }
   // insertion a la fin
   crt->suivant = NE;
   return ((liste *)maliste);
}

liste *inserer_bonne_place_pliste_par_cellule(liste *maliste, cellule *cel)
{
   liste *crt;
   // existance de la cellule a inserer
   if (!cel)
      return ((liste *)maliste);

   // existance de la liste (vide)
   if (est_vide_liste(maliste))
      return ((liste *)cel);

   // insertion au debut
   if (maliste->valeur >= cel->valeur)
   {
      cel->suivant = maliste;
      return ((liste *)cel);
   }

   // insertion au milieu ou a la fin
   crt = maliste;
   while (crt->suivant)
   {
      if (cel->valeur <= crt->suivant->valeur)
      {
         cel->suivant = crt->suivant;
         // crt->suivant = NE;
         // return ((liste*) maliste);
         break;
      }
      crt = crt->suivant;
   }
   // insertion a la fin ou au milieu
   crt->suivant = cel;
   return ((liste *)maliste);
}

// tris de la liste en utilisant l'insertion a bonne place
liste *trier_pliste(liste *maliste)
{
   liste *temp = init_null(); // initialiser une liste vide pour stocker les elements trier
   if (!maliste)
   { // verifier l'existance de la liste ou il est vide
      printf("la liste n'exist pas (pas allouer) \n");
      return NULL;
   }

   while (maliste)
   {
      int valeur = maliste->valeur;
      maliste = supprimer(maliste, 1);
      temp = inserer_bonne_place_pliste(temp, valeur);
   }

   return ((liste *)temp);
}

// fonction trie les valeurs saisies dans la liste en utilisant l'insertion a bonne place
liste *saisie_valeur_pliste(liste *maliste)
{
   int valeur, choix;
   do
   {
      printf("Entrer une valeur a inserer dans la liste: ");
      scanf("%d", &valeur);
      maliste = inserer_bonne_place_pliste(maliste, valeur);
      printf("Voulez-vous inserer une autre valeur? (1: Oui, 0: Non): ");
      scanf("%d", &choix);
   } while (choix == 1);
   return ((liste *)maliste);
}

// concatener deux listes
liste *concatener_listes(liste *l1, liste *l2)
{
   liste *l, *crt;
   l = (liste *)init_null();

   while (l1 && l2)
   {
      // prendre le 1er elemeent de 1er liste
      crt = l1;
      l1 = l1->suivant;
      crt->suivant = NULL;
      l = inserer_bonne_place_pliste_par_cellule(l, crt);

      // prendre le 1er elemeent de 2eme liste
      crt = l2;
      l2 = l2->suivant;
      crt->suivant = NULL;
      l = inserer_bonne_place_pliste_par_cellule(l, crt);
   } // fin du while(l1 && l2)

   // ajouter les elements restants de l1
   while (l1)
   {
      crt = l1;
      l1 = l1->suivant;
      crt->suivant = NULL;
      l = inserer_bonne_place_pliste_par_cellule(l, crt);
   }
   // ajouter les elements restants de l2
   while (l2)
   {
      crt = l2;
      l2 = l2->suivant;
      crt->suivant = NULL;
      l = inserer_bonne_place_pliste_par_cellule(l, crt);
   }
   return ((liste *)l);
}

void supprimer_doublons(liste *maliste)
{
   liste *crt = maliste;
   liste *crt2, *cellule_a_supprimer;
   if (!maliste)
      return;
   while (crt)
   {
      crt2 = crt;
      while (crt2->suivant)
      {
         if (crt->valeur == crt2->suivant->valeur)
         {
            cellule_a_supprimer = crt2->suivant;
            crt2->suivant = cellule_a_supprimer->suivant;
            free(cellule_a_supprimer);
         }
         else
         {
            crt2 = crt2->suivant;
         }
      }
      crt = crt->suivant;
   }
}
void afficher_liste(liste *maliste)
{
   liste *current = maliste;
   printf("Liste-> ");
   while (current != NULL)
   {
      printf("%d -> ", current->valeur);
      current = current->suivant;
   }
   printf("NULL\n");
}

void afficher_liste_recursive(liste *maliste)
{
   if (est_vide_liste(maliste))
   {
      printf("null\n");
      return;
   }
   printf("%d->", maliste->valeur);

   afficher_liste_recursive(maliste->suivant);
}


//* ================================ pile avec pointeurs =============================== //* //

typedef cellule Pile; // type pile

// creation du cellule
cellule *cree_cellule(int valeur)
{
   cellule *newCellule = (cellule *)malloc(sizeof(cellule));
   if (!newCellule)
      return NULL;

   newCellule->valeur = valeur;
   newCellule->suivant = NULL;

   return ((cellule *)newCellule);
}

Pile *init_pile()
{
   return ((Pile *)NULL);
}
// teseter si la pile est vide
int est_vide_pile(Pile *pile)
{
   return (pile == NULL);
}

// rerturner la taille d'un pile
int taille_recursive_pile(Pile *pile)
{ // il faut faire * pointeur pour ne pas ....
   if (est_vide_pile(pile))
      return 0;
   return ((int)(1 + taille_recursive_pile(pile->suivant)));
}

void test(Pile *mapile)
{
   mapile = mapile->suivant;
   mapile->valeur = 7;
   cellule *Ne = cree_cellule(5);
   mapile->suivant = Ne;
}
Pile *test2(Pile *mapile)
{
   cellule *Ne = cree_cellule(4);
   Ne->suivant = mapile;
   mapile = Ne;
   return ((Pile *)mapile);
}

// empiler
Pile *empiler_pile(Pile *pile, int valeur)
{
   cellule *nouveauElment = cree_cellule(valeur);
   if (!nouveauElment)
      return pile; // returner la pile originale si erreur d'allocation

   nouveauElment->suivant = pile;
   pile = nouveauElment;

   return ((Pile *)pile); // returner le nouveau sommet
};
Pile *depiler_pile(Pile *pile)
{
   if (!pile)
      return NULL;
   Pile *temp = pile;
   pile = pile->suivant;
   free(temp);
   return ((Pile *)pile);
}

Pile *inserer_bonne_place_pile(Pile *pile, int valeur)
{
   Pile *tmp = init_pile();

   // depiler jusqu'a trouver la bonne place
   while (pile)
   {
      if (pile->valeur >= valeur)
         break;
      tmp = empiler_pile(tmp, pile->valeur);
      pile = depiler_pile(pile);
   }

   // empiler la nouvelle valeur
   tmp = empiler_pile(tmp, valeur);

   // remettre les elements depiler
   while (tmp)
   {
      pile = empiler_pile(pile, tmp->valeur);
      tmp = depiler_pile(tmp);
   }

   return ((Pile *)pile);
}

Pile *inserer_bonne_place_pile_par_cellule(Pile *pile, cellule *cel)
{
   Pile *tmp = init_pile();
   cellule *crt;

   // depiler jusqu'a trouver la bonne place
   while (pile)
   {
      if (pile->valeur >= cel->valeur)
         break;
      crt = pile;           // reserver la cellule a deplacer
      pile = pile->suivant; // depiler par cellule en mettant a jour le pointeur
      crt->suivant = tmp;   // attacher la cellule a la pile tmp
      tmp = crt;            // mettre a jour le sommet de tmp
   }

   // empiler la nouvelle cellule
   cel->suivant = tmp;
   tmp = cel;

   // remettre les elements depiler
   while (tmp)
   {
      crt = tmp;           // sauvegarder la cellule courante
      tmp = tmp->suivant;  // avancer tmp
      crt->suivant = pile; // attacher la cellule a pile
      pile = crt;          // mettre a jour le sommet de pile
   }

   return ((Pile *)pile);
}
// tris de la pile en utilisant l'insertion a bonne place
Pile *trier_pile(Pile *pile)
{
   Pile *temp = init_pile();
   // la pile est vide, rien a trier
   if (!pile)
   { // verifier l'existance de la pile ou il est vide
      printf("la pile n'exist pas (pas allouer) \n");
      return NULL;
   }

   // parcourir la pile et inserer chaque element dans la pile temp a sa bonne place
   while (pile)
   {
      int valeur = pile->valeur;
      pile = depiler_pile(pile);
      temp = inserer_bonne_place_pile(temp, valeur);
   }
   return ((Pile *)temp);
}

// trouver le minimum dans la pile
int minimum_pile(Pile *pile)
{
   int min;
   Pile *tmp = init_pile();
   if (est_vide_pile(pile))
   {
      printf("Pile vide, pas de minimum.\n");
      exit(-1);
   }
   min = pile->valeur;

   // parcourir la pile pour trouver le minimum
   while (pile->suivant)
   {
      if (pile->valeur < min)
         min = pile->valeur;
      tmp = empiler_pile(tmp, pile->valeur);
      pile = depiler_pile(pile);
   }
   // remettre les elements depiler
   while (tmp)
   {
      pile = empiler_pile(pile, tmp->valeur);
      tmp = depiler_pile(tmp);
   }
   free(tmp);
   return ((int)min);
}

int recherche_recursive_pile_2(Pile *pile, int valeur, int position) // dernier element
{
   if (est_vide_pile(pile)) //
      return ((int)0);      // valeur non trouvee
   if (pile->valeur == valeur)
      return (position); // valeur trouvee
   return recherche_recursive_pile_2(pile->suivant, valeur, position + 1);
}

int recherche_recursive_pile(Pile *pile, int valeur)
{
   return recherche_recursive_pile_2(pile, valeur, 1);
}

void affichier_recursive(Pile *pile)
{
   if (!est_vide_pile(pile))
   {
      printf("%d ", pile->valeur);
      affichier_recursive(pile->suivant);
   }
}
void afficher_pile(Pile *mapile)
{
   Pile *tmp;
   tmp = init_pile();
   printf("Pile-> ");
   while (mapile)
   {
      printf("%d-> ", mapile->valeur);
      tmp = empiler_pile(tmp, mapile->valeur);
      mapile = depiler_pile(mapile);
   }
   printf("NULL\n");
   while (tmp)
   {
      mapile = empiler_pile(mapile, tmp->valeur);
      tmp = depiler_pile(tmp);
   }
   free(tmp);
}

//* ================================ file avec tableau =============================== //* //

#define TAILLE 10

typedef struct Tfile
{
   int tableau[TAILLE];
   int tete;
   int queue;
} Tfile;

// *********************************************************************************
Tfile *create_Tfile()
{
   Tfile *laTfile = (Tfile *)malloc(sizeof(Tfile));
   if (!laTfile)
      exit(-1); //! Erreur d'allocation mémoire
   return ((Tfile *)laTfile);
}

// *********************************************************************************

// inisialiser le tableau et tete et queue
int init_Tfile(Tfile *laTfile)
{
   if (!laTfile)
      return ((int)-1); //! Erreur : le tableau n'existe pas (utilisant un pointeur NULL)
   laTfile->tete = 0;
   laTfile->queue = -1;
   return ((int)0); //* Succès
}

// *********************************************************************************
// tester si la Tfile est vide
int est_vide_Tfile(Tfile laTfile) // works
{
   return ((int)(laTfile.queue < laTfile.tete)); // Retourne 1(true) si le tableau est vide, sinon 0 (false)
}

// *********************************************************************************
// tester si la Tfile est sature
int est_sature_Tfile(Tfile laTfile)
{
   return ((int)(laTfile.queue - laTfile.tete == TAILLE - 1)); // il va returne 1 si tete + queue = max du taille - 1
}

// *********************************************************************************
// returner le nombre d'element dans la Tfile
int nombre_elements_Tfile(Tfile laTfile) // works
{
   return ((int)(laTfile.queue - laTfile.tete + 1)); // Retourne le nombre d'éléments dans le tableau
}

// *********************************************************************************
// tasser la Tfile vers gauche pour ajouter l'espace unutilisable
int tasser_Tfile(Tfile *laTfile)
{
   int ind;
   if (!laTfile)
      return ((int)-1); //! Erreur : la Tfile n'exist pas
   for (ind = laTfile->tete; ind <= laTfile->queue; ind++)
      laTfile->tableau[ind - laTfile->tete] = laTfile->tableau[ind];
   laTfile->queue = laTfile->queue - laTfile->tete; // CHANGER LA VALEUR QUEUE
   laTfile->tete = 0;

   return ((int)2);
}

// enTfiler la Tfile: ajouter a la fin (concept FIFO: first in first out)
int enTfiler_Tfile(Tfile *laTfile, int valeur)
{
   int tasser = 1; // par defaut est non tasser (1 : non tasser,2:tasser)
   // Vérifier si le tableau est existant
   if (!laTfile)
      return ((int)-1); //! Erreur : le tableau n'existe pas
   if (est_sature_Tfile(*laTfile))
      return ((int)-4);             //! Erreur : fille est sature
   if (laTfile->queue == TAILLE - 1) //?si queue et dans la dernier element et n'est pas sature on va tasser
      tasser = tasser_Tfile(laTfile);
   laTfile->queue++;
   laTfile->tableau[laTfile->queue] = valeur;
   return ((int)tasser); // Succès
}
int enTfiler_Tfile_tableau_circulaire(Tfile *laTfile, int valeur)
{
   int tasser = 1; // par defaut est non tasser (1 : non tasser,2:tasser)
   // Vérifier si le tableau est existant
   if (!laTfile)
      return ((int)-1); //! Erreur : le tableau n'existe pas
   if (est_sature_Tfile(*laTfile))
      return ((int)-4);             //! Erreur : fille est sature
   if (laTfile->queue == TAILLE - 1) //?si queue et dans la dernier element et n'est pas sature on va tasser
      tasser = tasser_Tfile(laTfile);
   laTfile->queue++;
   laTfile->tableau[laTfile->queue] = valeur;
   return ((int)tasser); // Succès
}
// deTfiler : suppimer le debut (concept fifo first in first out)
int deTfiler_Tfile(Tfile *laTfile)
{
   int ind; // Indice de parcours
   if (!laTfile)
      return ((int)-1); //! Erreur : le tableau n'existe pas
   if (est_vide_Tfile(*laTfile))
      return ((int)-2); //! Erreur : le tableau est vide
   if (laTfile->tete == laTfile->queue)
      init_Tfile(laTfile);
   else
      laTfile->tete++;

   return ((int)0); // Succès
}

// *********************************************************************************
void afficher_Tfile(Tfile laTfile)
{
   int ind;
   for (ind = 0; ind < TAILLE; ind++)
   {
      if (ind >= laTfile.tete && ind <= laTfile.queue)
         printf("|%d", laTfile.tableau[ind]);
      else
         printf("| ");
   }
   printf("|   ");
   printf("tete: |%d|,queue: |%d|\n", laTfile.tete, laTfile.queue);
}

//* ================================ liste avec teableau =============================== //* //

// structure du tableau avec son indice du dernier element en definition leur type
typedef struct TList
{
   int tab[TAILLE];
   int indice_dr;
} TList;

// fonction de creation du tableau dynamique "allocation dynamique"
TList *create_tab()
{
   TList *liste = (TList *)malloc(sizeof(TList));
   if (!liste)
      exit(-1); // Erreur d'allocation mémoire
   return ((TList *)liste);
}

// inisialiser l'indice du dernier element du tableau a -1 pour indiquer qu'il est vide au debut
int init_ttab(TList *liste)
{
   if (!liste)
      return ((int)-1);   // Erreur : le tableau n'existe pas (utilisant un pointeur NULL)
   liste->indice_dr = -1; //? Initialiser l'indice du dernier élément
   return ((int)0);       // Succès
}

// fonction pour tester si un tableau est vide ou pas
int est_vide_ttab(TList liste)
{
   return ((int)(liste.indice_dr == -1)); // Retourne 1(true) si le tableau est vide, sinon 0 (false)
}

// fonction pour obtenir le nombre d'elements dans le tableau
int nombre_elements_ttab(TList liste)
{
   return ((int)(liste.indice_dr + 1)); // Retourne le nombre d'éléments dans le tableau
}

// fonction d'insertion d'une valeur a un indice specifique dans le tableau
int insertion(TList *liste, int indice, int valeur)
{
   int ind; // Indice de parcours
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   if (est_vide_ttab(*liste))
      return ((int)-2); // Erreur : le tableau est vide
   if ((indice < 0) || (indice > liste->indice_dr + 1))
      return ((int)-3); // Erreur : indice invalide
   if (liste->indice_dr >= TAILLE - 1)
      return ((int)-4); // Erreur : le tableau est sature

   // Décaler les éléments vers la droite
   for (ind = liste->indice_dr; ind >= indice; liste->tab[ind + 1] = liste->tab[ind], ind--)
      ;
   liste->tab[indice] = valeur;
   liste->indice_dr++;
   return ((int)0); // Succès
}

// fonction de suppression d'une valeur  par l'indice specifique dans le tableau
int supprimer_ttab(TList *liste, int indice)
{
   int ind; // Indice de parcours
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   if (est_vide_ttab(*liste))
      return ((int)-2); // Erreur : le tableau est vide
   if ((indice < 0) || (indice > liste->indice_dr))
      return ((int)-3); // Erreur : indice invalide

   // decaler les elements a gauche
   for (ind = indice; ind < liste->indice_dr; ind++)
      liste->tab[ind] = liste->tab[ind + 1];
   liste->indice_dr--; // Decrementer l'indice du dernier élément
   return ((int)0);    // Succès
}

// fonction de suppression de la premiere occurence d'une valeur dans le tableau
int supprimer_premier_occ_ttab(TList *liste, int valeur)
{
   int ind, indice_trouve = -1;
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   if (est_vide_ttab(*liste))
      return ((int)-2); // Erreur : le tableau est vide

   // Rechercher la première occurrence de la valeur
   for (ind = 0; ind <= liste->indice_dr; ind++)
   {
      if (liste->tab[ind] == valeur)
      {
         indice_trouve = ind;
         break;
      }
   }

   if (indice_trouve == -1)
      return ((int)-3); // Erreur : valeur non trouvée

   // Supprimer l'élément à l'indice trouvé
   for (ind = indice_trouve; ind < liste->indice_dr; ind++)
      liste->tab[ind] = liste->tab[ind + 1];
   liste->indice_dr--; // Decrementer l'indice du dernier élément
   return ((int)0);    // Succès
}

// fonction de suppression de toutes les occurences d'une valeur dans le tableau
int supprimer_tout_occurences_ttab(TList *liste, int valeur)
{
   int ind, count = 0;
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   if (est_vide_ttab(*liste))
      return ((int)-2); // Erreur : le tableau est vide

   ind = 0;
   while (ind <= liste->indice_dr)
   {
      if (liste->tab[ind] == valeur)
      {
         // Supprimer l'élément à l'indice trouvé
         for (int j = ind; j < liste->indice_dr; j++)
            liste->tab[j] = liste->tab[j + 1];
         liste->indice_dr--; // Decrementer l'indice du dernier élément
         count++;
      }
      else
      {
         ind++;
      }
   }

   if (count == 0)
      return ((int)-3); // Erreur : valeur non trouvée

   return ((int)count); // Retourne le nombre d'occurrences supprimées
}

// fonction de recherche d'une valeur dans le tableau
int recherche_ttab(TList liste, int valeur)
{
   int ind;
   for (ind = 0; ind <= liste.indice_dr; ind++)
      if (liste.tab[ind] == valeur)
         return ((int)ind); // Succès : valeur trouvée, retourne l'indice
   return ((int)-1);        // Erreur : valeur non trouvée
}

// fonction d'insertion d'une valeur a la fin du tableau
int insert_fin_ttab(TList *liste, int valeur)
{
   // Vérifier si le tableau est existant
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   // Vérifier si le tableau est sature
   if (liste->indice_dr == TAILLE - 1)
      return ((int)-2); // Erreur : le tableau est sature

   liste->indice_dr++;
   liste->tab[liste->indice_dr] = valeur;
   return (0); // Succès
}

// fonction de remplissage du tableau interactivement avec l'utilisateur
int remplir_ttab(TList *liste)
{
   int valeur, resultas;
   char c;
   if (!liste)          //   Verifier si le tableau est existant
      return ((int)-1); // Erreur : le tableau n'existe pas

   printf("\n===== REMPLISSAGE DU TABLEAU =====\n");

   do
   {
      printf("Entrez l'element %d/%d: ", liste->indice_dr + 2, TAILLE);
      scanf("%d", &valeur);
      resultas = insert_fin_ttab(liste, valeur);

      if (resultas == 0)
         printf(" -> Element %d ajoute avec succes a l'indice %d\n", valeur, liste->indice_dr);

      if (liste->indice_dr < TAILLE - 1) // Verifier si le tableau est completement rempli
      {
         printf("\nContinuer le remplissage ? (o/n): ");
         scanf(" %c", &c);
      }
      else
      {
         printf("\nTableau completement rempli!\n");
         break;
      }
      printf("\n--------------------------------\n");
   } while (((c != 'n') && (c != 'N')));

   printf("\n===== FIN DU REMPLISSAGE =====\n");
   return ((int)0); // Succès
}

// fonction d'affichage du tableau
void afficher_ttab(TList liste)
{
   int ind;

   for (ind = 0; ind < TAILLE; ind++)
      if (ind > liste.indice_dr)
         printf("| ");
      else
         printf("|%d", liste.tab[ind]);
}

// fonction de modification d'une valeur a un indice specifique dans le tableau
int modifier_ttab(TList *liste, int indice, int valeur)
{
   int ind;
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   if (est_vide_ttab(*liste))
      return ((int)-2); // Erreur : le tableau est vide
   if ((indice < 0) || (indice > liste->indice_dr))
      return ((int)-3); // Erreur : indice invalide
   liste->tab[indice] = valeur;
   return ((int)0); // Succès
}

// fonction de modification de la premier occurence d'une valeur dans le tableau
int modifier_premier_occ_ttab(TList *liste, int ancienne_valeur, int nouvelle_valeur)
{
   int ind, indice_trouve = -1;
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   if (est_vide_ttab(*liste))
      return ((int)-2); // Erreur : le tableau est vide

   // Rechercher la première occurrence de l'ancienne valeur
   for (ind = 0; ind <= liste->indice_dr; ind++)
   {
      if (liste->tab[ind] == ancienne_valeur)
      {
         indice_trouve = ind;
         break;
      }
   }

   if (indice_trouve == -1)
      return ((int)-3); // Erreur : valeur non trouvée

   // Modifier l'élément à l'indice trouvé
   liste->tab[indice_trouve] = nouvelle_valeur;
   return ((int)0); // Succès
}

// focntion de modification de toutes les occurences d'une valeur dans le tableau
int modifier_tout_occurences_ttab(TList *liste, int ancienne_valeur, int nouvelle_valeur)
{
   int ind, count = 0;
   if (!liste)
      return ((int)-1); // Erreur : le tableau n'existe pas
   if (est_vide_ttab(*liste))
      return ((int)-2); // Erreur : le tableau est vide

   // Parcourir le tableau pour modifier toutes les occurrences
   for (ind = 0; ind <= liste->indice_dr; ind++)
   {
      if (liste->tab[ind] == ancienne_valeur)
      {
         liste->tab[ind] = nouvelle_valeur;
         count++;
      }
   }

   if (count == 0)
      return ((int)-3); // Erreur : valeur non trouvée

   return ((int)count); // Retourne le nombre d'occurrences modifiées
}

// ====== Menu pour les fonctions  ======
int menu2()
{
   printf("\n===== MENU =====\n");
   printf("1. Remplir le tableau\n");
   printf("2. Afficher le tableau\n");
   printf("3. Rechercher une valeur dans le tableau\n");
   printf("4. Inserer une valeur dans le tableau\n");
   printf("5. Supprimer une valeur dans le tableau\n");
   printf("6. Modifier une valeur dans le tableau\n");
   printf("7. Nombre d'elements dans le tableau\n");
   printf("8. Quitter\n");
   printf("================\n");
   int choix;
   // en demande d'ecrire jusqu'au le nombre choisir est compris entre 1 et 8 (inclus 1 et 8)
   do
   {
      printf("Entrez votre choix: ");
      scanf("%d", &choix);
   } while (choix < 1 || choix > 8);
   return choix;
}

// === fonction des messages d'errors ===
void errors_message_ttab(int nombre)
{
   switch (nombre)
   {
   case -1:
      printf("Le tableau n'existe pas.\n");
      break;
   case -2:
      printf("Le tableau est vide.\n");
      break;
   case -3:
      printf("Indice invalide.\n");
      break;
   case -4:
      printf("Le tableau est sature.\n");
      break;

   default:
      printf("problem inconue\n");
      break;
   }
}






//* ================================ pile avec tableau =============================== //* //



// Definition de la structure Tpile
typedef struct Tpile
{
   int tableau[TAILLE];
   int sommet;
} Tpile;

// creer la pile
Tpile *create_tpile()
{
   Tpile *maTpile = (Tpile *)malloc(sizeof(Tpile));
   if (!maTpile)
   {
      printf("Erreur de mémoire !\n");
      exit(0);
   }
   return maTpile;
}

// initialiser la pile
int init_tpile(Tpile *maTpile)
{
   // tester l'existance
   if (!maTpile)
      return ((int)-1);
   maTpile->sommet = -1; // initialiser le sommet a -1
   return 1;
}

// test de vide
int est_vide_tpile(Tpile maTpile)
{
   return ((int)maTpile.sommet == -1);
}

// test de saturatoin
int est_sature_tpile(Tpile mapile)
{
   return ((int)(mapile.sommet) == (TAILLE - 1));
}

// empiler
int empiler_tpile(Tpile *mapile, int valeur)
{
   // tester l'existance
   if (!mapile)
      return ((int)-1);
   // tester saturation
   if (est_sature_tpile(*mapile))
      return ((int)-2);

   mapile->tableau[++(mapile->sommet)] = valeur;
   return ((int)1);
}

// depiler
int depiler_tpile(Tpile *mapile)
{
   // tester l'existance
   if (!mapile)
      return ((int)-1);
   // tester si il est vide
   if (est_vide_tpile(*mapile))
      return ((int)-3);
   (mapile->sommet)--;
   return ((int)1);
}

// afficher la pile sans la modifier en utilisant une pile temporaire pour conserver le principe LIFO
void afficher_tpile(Tpile mapile)
{
   if (est_vide_tpile(mapile))
   {
      printf("Tpile vide\n");
      return;
   }

   // Sauvegarder les valeurs dans un tableau temporaire
   int temp[TAILLE];
   int nb_elements = 0;

   printf("Affichage LIFO: \n");
   // Phase 1: Dépiler et sauvegarder
   while (!est_vide_tpile(mapile))
   {
      temp[nb_elements] = mapile.tableau[mapile.sommet];
      printf("pile[%d]=%d\n", mapile.sommet, temp[nb_elements]);
      depiler_tpile(&mapile);
      nb_elements++;
   }

   // Phase 2: Restaurer la pile
   for (int i = nb_elements - 1; i >= 0; i--)
   {
      empiler_tpile(&mapile, temp[i]);
   }

   printf("\n");
}

// afficher la pile sans la modifier en utilisant une pile temporaire pour conserver le principe LIFO

// Simpler version using array instead of another pile
void afficher_tpile2(Tpile *mapile)
{
   if (est_vide_tpile(*mapile))
   {
      printf("Tpile vide\n");
      return;
   }

   // Save values in temporary array
   int temp[TAILLE];
   int count = 0;
   
   printf("Affichage LIFO: \n");
   
   // Phase 1: Save and display
   while (!est_vide_tpile(*mapile))
   {
      temp[count] = mapile->tableau[mapile->sommet];
      printf("pile[%d]=%d\n", mapile->sommet, temp[count]);
      depiler_tpile(mapile);
      count++;
   }

   // Phase 2: Restore pile
   for (int i = count - 1; i >= 0; i--)
   {
      empiler_tpile(mapile, temp[i]);
   }
   
   printf("\n");
}
// Fonction pour empiler par passage de valeur (retourne une nouvelle pile)
static inline Tpile *empiler_tpile_passage_valeu(Tpile pile, int valeur)
{
   Tpile *nouvelle_pile = create_tpile();
   if (!nouvelle_pile)
      return NULL;
   
   // Copier la pile originale
   *nouvelle_pile = pile;
   
   // Empiler la nouvelle valeur
   int result = empiler_tpile(nouvelle_pile, valeur);
   if (result != 1) {
      free(nouvelle_pile);
      return NULL;
   }
   
   return nouvelle_pile;
}


#endif // POINTEUR_FILE_COMPLETE_H
