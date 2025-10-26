#include <stdio.h>
#include <stdlib.h>

typedef struct cellule
{
   int valeur;
   struct cellule *suivant;
} cellule;

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

// Afficher le menu pour l'utilisateur
void afficher_menu()
{
   printf("\n=== Menu ===\n");
   printf("1. Inserer une valeur\n");
   printf("2. Supprimer un element par position\n");
   printf("3. Supprimer premiere occurrence d'une valeur\n");
   printf("4. Supprimer toutes les occurrences d'une valeur\n");
   printf("5. Modifier une valeur par position\n");
   printf("6. Modifier toutes les occurrences d'une valeur\n");
   printf("7. Afficher la liste\n");
   printf("8. Afficher la taille de la liste\n");
   printf("0. Quitter\n");
   printf("Choix: ");
}

// Executer le menu interactif
void exec()
{
   liste *maliste = (liste *)init_null();
   int choix, valeur, position, nouvelle_valeur, valeur_a_changer;

   do
   {
      afficher_menu();
      scanf("%d", &choix);

      switch (choix)
      {
      case 1:
         printf("Valeur a inserer: ");
         scanf("%d", &valeur);
         printf("Position: ");
         scanf("%d", &position);
         maliste = inserer_liste(maliste, valeur, position);
         break;
      case 2:
         printf("Position a supprimer: ");
         scanf("%d", &position);
         maliste = supprimer(maliste, position);
         break;
      case 3:
         printf("Valeur a supprimer: ");
         scanf("%d", &valeur);
         maliste = supprimer_prem_occu(maliste, valeur);
         break;
      case 4:
         printf("Valeur a supprimer: ");
         scanf("%d", &valeur);
         maliste = supprimer_tout_occu(maliste, valeur);
         break;
      case 5:
         printf("Position a modifier: ");
         scanf("%d", &position);
         printf("Nouvelle valeur: ");
         scanf("%d", &nouvelle_valeur);
         maliste = modifier_liste(maliste, position, nouvelle_valeur);
         break;
      case 6:
         printf("Valeur a chercher: ");
         scanf("%d", &valeur_a_changer);
         printf("Nouvelle valeur: ");
         scanf("%d", &valeur);
         maliste = modifier_liste_touts_valeur(maliste, valeur, valeur_a_changer);
         break;
      case 7:
         afficher_liste(maliste);
         break;
      case 8:
         printf("Taille de la liste: %d\n", taille_liste_recursive(maliste));
         break;
      case 0:
         printf("Au revoir!\n");
         break;
      default:
         printf("Choix invalide!\n");
      }
   } while (choix != 0);
}

int main()
{
   // Creer une liste vide
   liste *maliste = init_null();
   printf("\n\n========== Test des fonctions de la liste chaine (pointeur) ==========\n\n");
   if (!maliste)
   {
      printf("La liste est initialisee a NULL.\n");
   }

   // Test insertion
   printf("\n1. Test d'insertion par position:\n");
   maliste = inserer_liste(maliste, 10, 1);
   maliste = inserer_liste(maliste, 20, 1);
   maliste = inserer_liste(maliste, 40, 1);
   maliste = inserer_liste(maliste, 25, 1);
   maliste = inserer_liste(maliste, 40, 1);
   maliste = inserer_liste(maliste, 30, 1);
   maliste = inserer_liste(maliste, 40, 1);

   printf("afficher la liste apres insertions: ");
   afficher_liste(maliste);

   // la taille
   printf("\n2. Taille de la liste apres insertions: %d\n", taille_liste_recursive(maliste));
   // Test modification
   printf("\n3. Test de modification par position:\n");
   printf("modifier la position 2 avec la valeur 25\n");
   maliste = modifier_liste(maliste, 2, 25);
   printf("Apres modification: ");
   afficher_liste(maliste);

   // Test suppression par position
   printf("\n4. Test de suppression par position:\n");
   printf("supprimer la position 1\n");
   maliste = supprimer(maliste, 1);
   printf("Apres suppression: ");
   afficher_liste(maliste);

   // Test suppression par valeur
   printf("\n5. Test de suppression par valeur (25):\n");
   maliste = supprimer_prem_occu(maliste, 25);
   printf("Apres suppression premiere occurrence de 25: ");
   afficher_liste(maliste);

   // Test suppression toutes occurrences
   printf("\n6. Test de suppression de toutes les occurrences(40):\n");
   maliste = supprimer_tout_occu(maliste, 40);
   printf("Apres suppression de tous les 40: ");
   afficher_liste(maliste);

   // Afficher la taille
   printf("\n6. Taille de la liste: %d\n", taille_liste_recursive(maliste));

   // Liberer la memoire
   printf("\nNettoyage de la liste...\n");
   while (!est_vide_liste(maliste))
   {
      maliste = supprimer(maliste, 1);
   }
   printf("Liste finale: ");
   afficher_liste(maliste);

   return 0;
}