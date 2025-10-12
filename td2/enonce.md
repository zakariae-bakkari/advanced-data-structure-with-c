## Page 1

**Filière Ingénieur : ILISI**
**Structures de Données** 
**Exercices: Langage C** 

---

### I Les chaînes de caractères

Donner un programme en langage C qui permet de lire une phrase, au clavier  et d'indiquer si un mot donné, lui aussi au clavier, par l'utilisateur se trouve dans cette phrase

---

### II Le compte est bon

Le but du jeu "le compte est bon" est de déterminer la combinaison des opérations arithmétiques ($(+, -, *, /)$) à appliquer sur trois nombres pour obtenir une valeur donnés $S$ À défaut d'obtenir $S$, il faut déterminer le nombre le plus proche de la valeur choisie $S$

---

### III Le palindrome

Un "palindrome" est un mot qui peut se lire de la droite vers la gauche et de la gauche vers la droite avec la même signification
Exemples: ABBA, RADAR, NOYON 
Nous désirons lire une ligne de texte et imprimer à l'écran tous les mots palindromes qui s'y trouvent
Effectuer une **analyse du problème** puis donner l'**algorithme équivalent** et enfin le **programme en langage C**

---

### IV Une image

Une image peut être représentée par une table à deux dimensions Chaque élément de cette table correspond à un point (pixel) qui apparaît sur l'écran avec une nuance de niveau de gris Chaque pixel de cette image peut avoir une valeur codée sur un octet (entre 0 et 255)
Je désire comptabiliser le nombre d'occurrences des niveaux de gris sur une image L'image est supposée déjà saisie
Définissez la **structure de données** adéquate pour réaliser cette opération de comptage des niveaux de gris de l'image
Donnez l'**algorithme** qui permet de compter le nombre de fois qu'un niveau de gris est apparu dans une image donnée

---

### V Les listes ($2^e$ contrôle $96/97$) 

a) Rappeler la **structure de données** d'une **liste doublement chaînée**
b) Écrivez l'**algorithme** permettant de faire la **fusion** de deux liste L1 et L2 doublement chaînées La liste L2 est mise à la suite de la liste L1
c) Écrivez l'**algorithme** permettant de **couper** à la position N une liste L doublement chaînée en deux liste L1 et L2
d) Écrivez l'**algorithme** de la fonction qui donne la **longueur** d'une liste


## Page 2

**Filière Ingénieur: ILISI** 
**Structures de Données** 
**Exercices sur les listes et les piles** 

---

### I Les tris

Nous désirons **trier** des entiers saisis au clavier, à l'aide des **listes chaînées**, dans un ordre croissant Le tri doit s'effectuer au fur et à mesure que les entiers sont saisis Pour cela:
a- définissez la **structure de données** 
b- donnez l'**algorithme** utilisant cette structure de données permettant de saisir des entiers et de les trier puis d'afficher le résultat.
c- traduisez en **langage C** cet algorithme

---

### II°) Concaténation de deux listes

Soient deux **listes simplement chaînées** L1 et L2. Elles contiennent des nombres entiers dans un ordre quelconque
a) Donner la **structure de données** relative à ce type de listes
b) Donner un **algorithme** permettant la **concaténation** des deux listes L1 et L2 dans une nouvelle liste L triée Le tri doit être réalisé au moment de la construction de L La concaténation est effectuée en prenant à tour de rôle un élément de chaque liste L1 et L2
c) Traduisez cet **algorithme en langage C**

---

### III°) Suppression des doublons dans une liste

Donner l'**algorithme** puis le **programme** qui permet de **supprimer les entiers qui figurent plusieurs fois** dans une liste chaînée

---

### IV°) Recherche du minimum dans une pile

a- Donnez une **fonction** qui effectue la **recherche du minimum** et de son rang parmi une suite de nombres dans une **pile**
Remarques: la pile est supposée déjà saisie

---

### V°) Suppression des doublons dans une pile

Donner l'**algorithme** puis le **programme** qui permet de **supprimer les entiers qui figurent plusieurs fois** dans une pile

---

### VI°) Mise en neurones

Après analyse, donner un **programme en Langage C** permettant de déterminer dans une **liste chaînée** supposée déjà initialisée la **plus grande occurrence** (occurrence = suite d'éléments identiques), le **rang** du premier élément de cette occurrence, le **nombre d'éléments** la composant et enfin l'**affichage** de cette occurrence
Justifier vos choix
Remarque: s'il y a deux occurrences de même longueur seule la première dans la liste chaînée sera prise en considération

..... 

## Page 3

**Filière Ingénieur: ILISI** 
**Structures de Données** 
**Exercices: les arbres** 

---

### I°)

Soit l'expression mathématique suivante: $a+b/c*d+d*c/b-a$ 
Représenter cette expression mathématique sous forme d'**arbre binaire** Expliquer et justifier la construction de cet arbre Donner les résultats du **parcours de différentes façons** de cet arbre

---

### II°) Expression mathématique

Soit l'expression arithmétique suivante: $Exp=(((a+b)*c)+(d+c)+f)$ 
a) Donner une **représentation** de cette expression sous forme d'un **arbre** sans faire apparaître les parenthèses sur cet arbre
b) Indiquer la **racine**, les **feuilles** et la **longueur** de cet arbre
c) Donner l'ensemble des **feuilles à droite** (respectivement **à gauche**) de la feuille "d"
f) Donner les **parcours préfixé, infixé et postfixé** de cet arbre
g) Comparez le résultat de l'expression arithmétique "Exp" et du résultat du parcourt infixé pour les valeurs suivantes: $a=2$, $b=4$, $c=3$, $d=2$ et $f=3$ Vos remarques

---

### III°) Recherche du minimum dans un arbre

a- Donner une **fonction** qui effectue la **recherche du minimum** parmi une suite de nombres dans un **arbre binaire**
Remarques: l'arbre est supposé déjà saisi

---

### IV°) Arbre et liste

Donner l'**algorithme** puis le **programme** permettant de lire des entiers mis dans un **arbre binaire**, Arb supposé déjà saisi, est de les mettrent dans une **liste simplement chaînée**, Liste
Puis d'**afficher** cette liste Préciser la **structure de données** adoptée pour l'arbre et la liste

---

### V°) Les arbres: recherche d'un élément dans un arbre

Soit un **arbre binaire d'entiers parfaitement équilibré** déjà initialisé Nous souhaitons voir si un entier existe dans cet arbre et, si tel est le cas, retourner sa **position** dans l'arbre
Donner l'**algorithme** et la **fonction en langage C** de la fonction réalisant cela Mise en œuvre à l'aide des **pointeurs**
Remarque: l'arbre est supposé déjà initialisé et dans cet arbre un nombre n'apparaît qu'une seule fois Donner seulement la fonction qui reçoit comme arguments un entier et un arbre puis retourne la position de cet entier
