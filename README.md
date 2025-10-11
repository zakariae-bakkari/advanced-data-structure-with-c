# Structures de Données Avancées - TD/TP

Ce repository contient les exercices et implémentations des structures de données avancées du semestre 1.

## 📚 Contenu

### Structures Implémentées

- **Files (Queues)**
  - `pileTableau.c` - Implémentation avec tableau statique
  - `pilePointeur.c` - Implémentation avec pointeurs et listes chaînées

### Concepts Couverts

- **FIFO (First In, First Out)** - Principe des files
- **Gestion mémoire dynamique** - Allocation et libération
- **Pointeurs et structures** - Manipulation avancée
- **Algorithmes de base** - Insertion, suppression, recherche

## 🚀 Compilation

```bash
gcc pileTableau.c -o pileTableau
gcc pilePointeur.c -o pilePointeur
```

## 📋 Fonctionnalités

### File avec Tableau
- ✅ Création et initialisation
- ✅ Enfiler/Défiler (FIFO)
- ✅ Tests de saturation et de vide
- ✅ Tassement automatique
- ✅ Affichage et comptage

### File avec Pointeurs
- 🔄 En cours de développement
- ⚠️ Structure à optimiser (pointeurs vs objets)

## 🛠️ Structure du Code

```
exercices/
├── pileTableau.c      # Implémentation tableau
├── pilePointeur.c     # Implémentation pointeurs
├── .gitignore         # Exclusions Git
└── README.md          # Ce fichier
```

## 📖 Utilisation

### Menu Interactif
1. Enfiler un élément
2. Afficher la file
3. Défiler un élément
4. Compter les éléments
5. Tester si vide
6. Tester si saturée
7. Quitter

## 🔧 Notes Techniques

- **Taille maximale** : 10 éléments (modifiable via `#define maxelem`)
- **Gestion d'erreurs** : Codes de retour standardisés
- **Optimisation** : Tassement automatique pour réutiliser l'espace

## 📝 État du Projet

- [x] File avec tableau - Fonctionnelle
- [ ] File avec pointeurs - En développement
- [ ] Tests unitaires
- [ ] Documentation détaillée

## 👨‍💻 Auteur

Zakariae bakkari : Étudiant FST - Semestre 1
Structure de Données Avancées

---

*Ce projet fait partie des travaux dirigés et travaux pratiques du cours de structures de données avancées.*