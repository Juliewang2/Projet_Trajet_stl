# Système de Gestion de Trajets

##  Description

Ce projet est une application console C++ pour la gestion et la recherche de trajets. Il permet de créer, stocker, et rechercher des itinéraires entre différentes villes en utilisant des structures de données avancées et des algorithmes de graphes.

##  Fonctionnalités

-  **Ajout de trajets simples** : Créer un trajet direct entre deux villes
-  **Ajout de trajets composés** : Créer un itinéraire avec plusieurs étapes
-  **Affichage du catalogue** : Visualiser tous les trajets enregistrés
-  **Recherche d'itinéraires** : Trouver tous les chemins possibles entre deux villes
-  **Chemin le plus court** : Calculer l'itinéraire optimal (algorithme de Dijkstra)
- **Sauvegarde/Chargement** : Persister les données dans des fichiers
-  **Détection de doublons** : Éviter l'ajout de trajets identiques

## Architecture

Le projet suit une architecture orientée objet avec les classes suivantes :

```
Trajet (classe abstraite)
    ├── TrajetSimple      : Trajet direct A → B
    └── TrajetCompose     : Trajet multi-étapes A → B → C → ...

Catalogue                 : Gestion de la collection de trajets
Graphe                    : Structure de données pour la recherche de chemins
```

### Diagramme de classes simplifié

```
┌─────────────────┐
│     Trajet      │ (abstract)
├─────────────────┤
│ - villeDepart   │
│ - villeArrive   │
│ - transport     │
├─────────────────┤
│ + Afficher()    │
│ + GetLongueur() │
│ + clone()       │
└────────┬────────┘
         │
    ┌────┴────┐
    │         │
┌───▼──────┐  ┌────▼─────────┐
│  Simple  │  │   Compose    │
├──────────┤  ├──────────────┤
│+ longueur│  │+ etapes[]    │
│          │  │+ NbEtapes()  │
└──────────┘  └──────────────┘
```

##  Structure des fichiers

```
.
├── main.cpp              # Point d'entrée et interface utilisateur
├── Trajet.h/cpp          # Classe de base abstraite
├── TrajetSimple.h/cpp    # Trajet simple (une seule liaison)
├── TrajetCompose.h/cpp   # Trajet composé (plusieurs étapes)
├── Catalogue.h/cpp       # Gestion de la collection de trajets
├── Graphe.h/cpp          # Algorithmes de recherche (DFS, Dijkstra)
├── makefile              # Compilation du projet
└── README.md             # Ce fichier
```

##  Compilation et Exécution

### Prérequis

- **Compilateur C++** : g++ avec support C++17
- **Make** : Pour utiliser le makefile

### Compilation

```bash
make
```

Cela génère l'exécutable `projet`.

### Exécution

```bash
./projet
```

### Nettoyage

```bash
make clean
```

##  Utilisation

### Menu principal

Au lancement, vous verrez le menu suivant :

```
1: Ajout d'un Trajet Simple
2: Ajout d'un Trajet Composé
3: Affichage du Catalogue
4: Recherche d'itinéraires possible pour un road trip
5: Quitter l'application
6: Sauvegarder le catalogue dans un fichier
7: Charger le catalogue depuis un fichier
8: Trouver le chemin le plus court
```

### Exemples d'utilisation

#### 1. Ajouter un trajet simple

```
CHOIX => : 1
veuillez entrer une ville de départ: Paris
veuillez entrer une ville d'arrivée: Lyon
veuillez donner un moyen de transport: Train
Longueur de trajet: 450
trajet bien ajouté
```

#### 2. Ajouter un trajet composé

```
CHOIX => : 2
Veuillez entrer un nombre étape: 2

trajet number 1:
veuillez entrer une ville de départ: Paris
veuillez entrer une ville d'arrivée: Dijon
veuillez donner un moyen de transport: Train
Longueur de trajet: 300

trajet number 2:
veuillez entrer une ville de départ: Dijon
veuillez entrer une ville d'arrivée: Lyon
veuillez donner un moyen de transport: Bus
Longueur de trajet: 200

trajet bien ajouté
```

#### 3. Rechercher tous les chemins

```
CHOIX => : 4
Ville de depart : Paris
Ville d'arrive : Lyon
Paris Lyon
Paris Dijon Lyon
```

#### 4. Trouver le chemin le plus court

```
CHOIX => : 8
Ville de depart : Paris
Ville d'arrive : Lyon
Paris Lyon
```

#### 5. Sauvegarder le catalogue

```
CHOIX => : 6
Nom du fichier à sauvgarder : trajets.txt
```

Format du fichier de sauvegarde :
```
S Paris Lyon Train 450
C 2
S Paris Dijon Train 300
S Dijon Lyon Bus 200
```

#### 6. Charger un catalogue

```
CHOIX => : 7
Nom du fichier à charger : trajets.txt
```

##  Algorithmes implémentés

### 1. DFS (Depth-First Search)
- **Fonction** : `Graphe::ChercherCheminsPossibles()`
- **Complexité** : O(V + E) où V = nombre de villes, E = nombre de trajets
- **Usage** : Trouve tous les chemins possibles entre deux villes

### 2. Dijkstra
- **Fonction** : `Graphe::ChercherPlusCourtChemin()`
- **Complexité** : O((V + E) log V)
- **Usage** : Trouve le chemin le plus court en termes de distance totale

##  Gestion des erreurs

Le programme gère les cas suivants :

-  Trajets avec ville de départ = ville d'arrivée (refusé)
- Trajets composés avec liaisons invalides (non consécutives)
-  Doublons (détection automatique)
-  Fichiers inexistants lors du chargement
-  Entrées utilisateur invalides

##  Concepts C++ utilisés

### Polymorphisme
```cpp
vector<Trajet*> catalogue;  // Peut stocker TrajetSimple et TrajetCompose
```

### Classes abstraites
```cpp
class Trajet {
    virtual int GetLongueur() const = 0;  // Méthode pure virtuelle
    virtual Trajet* clone() const = 0;
};
```

### dynamic_cast
```cpp
// Conversion sécurisée de Trajet* vers TrajetSimple*
TrajetSimple* ts = dynamic_cast<TrajetSimple*>(trajet);
if (ts) {
    // Conversion réussie
}
```

### Templates STL
- `vector` : Stockage dynamique
- `map` : Graphe et distances
- `priority_queue` : Algorithme de Dijkstra

## Format de sauvegarde

### Trajet Simple
```
S <villeDepart> <villeArrive> <transport> <longueur>
```
Exemple : `S Paris Lyon Train 450`

### Trajet Composé
```
C <nombreEtapes>
S <dep1> <arr1> <trans1> <long1>
S <dep2> <arr2> <trans2> <long2>
...
```
Exemple :
```
C 2
S Paris Dijon Train 300
S Dijon Lyon Bus 200
```

##  Corrections apportées

### Problèmes résolus

1. **Faute de frappe** : `TrajetSiple` → `TrajetSimple`
2. **Incohérence de noms** : `Sauvegarder` vs `Sauvgarder` (uniformisé)
3. **Conversion de types** : `vector<TrajetSimple*>` → `vector<Trajet*>` pour la compatibilité
4. **dynamic_cast manquant** : Ajout de conversions sécurisées dans `Catalogue::Equals()`
5. **Mise à jour du graphe** : Ajout de `graphe.AjouterTrajet()` dans `Catalogue::AjouterTrajet()`

##  Améliorations possibles

- [ ] Interface graphique (Qt)
- [ ] Base de données (SQLite)
- [ ] Support de plusieurs moyens de transport pour un même trajet
- [ ] Calcul du temps de trajet en plus de la distance
- [ ] Export vers formats CSV/JSON
- [ ] Recherche avec contraintes (éviter certaines villes, moyens de transport préférés)
- [ ] Tests unitaires (Google Test)

##  Auteurs
WANG JIAYI
Projet académique - Cours de C++

## Licence

Ce projet est à usage éducatif.

##  Support

Pour toute question ou problème :
1. Vérifiez que vous utilisez C++17 ou supérieur
2. Assurez-vous que tous les fichiers sont présents
3. Compilez avec `make clean && make`

---

**Version** : 1.0  
**Dernière mise à jour** : Février 2026
