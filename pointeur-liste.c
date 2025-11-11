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

liste *inserer_bonne_place_pliste_par_cellule(liste *maliste, cellule *cel){
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
liste *saisie_valeur_pliste(liste *maliste){
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
   }// fin du while(l1 && l2)

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
   return ((liste*)l);
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
   // tester la fonction inserer_bonne_place_pliste
   printf("\n7. Test d'insertion en ordre croissant:\n");
   maliste = inserer_bonne_place_pliste(maliste, 50);
   maliste = inserer_bonne_place_pliste(maliste, 20);
   maliste = inserer_bonne_place_pliste(maliste, 30);
   maliste = inserer_bonne_place_pliste(maliste, 10);
   maliste = inserer_bonne_place_pliste(maliste, 40);
   printf("Apres insertions en ordre croissant: ");
   afficher_liste(maliste);
   //tester l'insertion par cellule
   printf("\n7.b Test d'insertion en ordre croissant par cellule:\n");
   cellule *cel = createcellule(25);
   maliste = inserer_bonne_place_pliste_par_cellule(maliste, cel);
   printf("Apres insertion de 25 par cellule en ordre croissant: "); 
   afficher_liste(maliste);

   // tester la fonction trier_pliste
   printf("\n8. Test de tri de la liste:\n");
   liste *unsorted_list = init_null();
   unsorted_list = inserer_liste(unsorted_list, 30, 1);
   unsorted_list = inserer_liste(unsorted_list, 10, 1);
   unsorted_list = inserer_liste(unsorted_list, 50, 1);
   unsorted_list = inserer_liste(unsorted_list, 20, 1);
   unsorted_list = inserer_liste(unsorted_list, 40, 1);
   printf("Liste non triee: ");
   afficher_liste(unsorted_list);
   liste *sorted_list = trier_pliste(unsorted_list);
   printf("Liste triee: ");
   afficher_liste(sorted_list);

   // tester la fonction concatener_listes
   printf("\n9. Test de concatenation de deux listes:\n");
   liste *l1 = init_null();
   liste *l2 = init_null();
   l1 = inserer_liste(l1, 10, 1);
   l1 = inserer_liste(l1, 30, 1);
   l1 = inserer_liste(l1, 50, 1);
   // tester concatener l1 et l2 tel que l2 est vide
   printf("Concatenation de l1 et l2 (l2 vide):\n");
   liste *concat1 = concatener_listes(l1, l2);
   afficher_liste(concat1);
   l1 = init_null();
   l1 = inserer_liste(l1, 10, 1);
   l1 = inserer_liste(l1, 30, 1);
   l1 = inserer_liste(l1, 50, 1);
   
   l2 = inserer_liste(l2, 20, 1);
   l2 = inserer_liste(l2, 40, 1);
   l2 = inserer_liste(l2, 60, 1);
   // tester concatener l1 et l2
   //afficher les deux
   printf("Liste l1: ");
   afficher_liste(l1);
   printf("Liste l2: ");
   afficher_liste(l2);
   printf("Concatenation de l1 et l2:\n");
   liste *concat2 = concatener_listes(l1, l2);
   afficher_liste(concat2);
   afficher_liste(l1); // verifier que l1 est intact
   afficher_liste(l2); // verifier que l2 est intact

   // tester la fonction saisie_valeur_pliste
   printf("\n10. Test de saisie de valeurs avec insertion en ordre croissant:\n");
   liste *saisie_list = init_null();
   saisie_list = saisie_valeur_pliste(saisie_list);
   printf("Liste apres saisie et insertion en ordre croissant: ");
   afficher_liste(saisie_list);
   
   return 0;
}