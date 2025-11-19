#include "touts.h"
// Fonction : Programme principal de test
// Entree : aucune
// Sortie : 0 en fin d'execution
// Description : Teste toutes les fonctionnalites de la pile avec la methode de la case libre.
int main() {
    printf("\n\n========== Test de la liste avec tableau cerc ==========\n\n");
    tliste_circ* tabtest = creer_tliste_circ();
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

    int valeur =10;
    printf("\nrechercher la valeur 10 : ");
    if(recherche_tliste_circ(*tabtest, valeur))
        printf("Valeur trouvée\n");
    else
        printf("Valeur non trouvée\n");

    printf("\nInsertion de 8 au rang 3...\n");
    insertion_tliste_circ(tabtest, 8, 3);
    afficher_tliste_circ(*tabtest);
    printf("\n\n========== fin de test ==========\n\n");





    // ===== file 
    printf("\n\n========== Test de la file avec tableau cerc ==========\n\n");
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
    int val =4;
    printf("chercher la valeur 4 : ");
    if (recherche_tfile(*mafile, val))
        printf("Valeur trouvée !\n");
    else
        printf("Valeur non trouvée.\n");

        printf("\n\n========== Fin de Test ==========\n\n");




   // === CREATION ET INITIALISATION ===
   printf("\n========== Test de la pile (methode de la case libre utilisee pour affichage) ==========\n\n");
   
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