# Sujet TD&P n°5 - Séances n°7 et 8

![Junia Banner](/documents/images/junia_banner.jpeg "Junia Banner")

- [ ] Rajouter des "test" pour chaque utilisation de fonctions pour détailler le fonctionnement
- [ ] Essayer d'avoir des affichages détaillés pour chaque chemin améliorant
- [ ] Répondre aux questions et rajouter les écrans dans le rapport git

**Objectifs** : Comprendre, développer et expérimenter l’algorithme de Ford-Fulkerson sur les différentes situations proposées. Ce TD&P noté devrait mettre en valeur la puissance d’une modélisation d’un problème réel en un problème de flots dans un graphe. Au travers d’une application concrète, on cherche à satisfaire les consommations localisées d’un produit manufacturé selon la capacité de production, de transport, et de stockage de plusieurs usines de fabrication.

## Table de matière :

1. [Trace de l’algorithme de Ford-Fulkerson.](#trace-de-l'agorithme-de-Ford-Fulkerson)

2. [Implémentation de l’algorithme de parcours en largeur puis de l’algorithme de Ford-Fulkerson qui se servira du parcours.](#partie-2)

- [Étape 1 : Représentation mémoire du graphe][#Étape1]
- [Étape 2. Le parcours en largeur au service de la recherche du chemin améliorant.][#Étape2]

3. [Compréhension et modélisation de problèmes réels en graphes et recherche du flot maximum dans ces derniers. Les arcs des graphes supportent des capacités.](#problèmes-réels)

Partie 4. A vous de jouer sur l’écriture d’un algorithme qui va calculer le coût minimal d’un flot dont la valeur (i.e., le nombre d’unités) a déjà été calculée. Les arcs des graphes supportent des capacités et des coûts.

Bonus.

## Trace de l'agorithme de Ford-Fulkerson

## Partie 2

**Etape 1**

Nous allons tout d’abord enregistrer un graphe en mémoire avec les techniques vues en cours.

- **Question** : Quelle matrice est donnée en exemple dans le cours pour à la fois enregistrer l’existence d’un arc mais aussi leur poids (i.e., leur coût).

La matrice donnée dans le cours est la matrice d’adjacence Madj :

![Matrice Adjacence](/documents/images/matriceAdjacence.png "Matrice Adjacence")

- **Question** : Expliquez l’intérêt des coûts infinis dans une telle matrice.
  
L’intérêt des coûts infinis dans une telle matrice est de représenter l’absence de liaison entre 2 sommets. Dans les algorithmes de recherche de chemin comme Dijkstra ou Bellman-Ford, les coûts infinis sont utilisés pour indiquer des chemins non parcourables ou des chemins qui n'existent pas.

Nous allons utiliser 2 matrices du même type pour sauvegarder les informations d’un graphe. L’une enregistrera les capacités, l’autre les coûts de chaque arc. La matrice des coûts ne sera utilisée qu’en partie 4 : nous travaillerons d’abord sur la matrice des capacités puisque le gros du travail consistera à trouver un flot max dans les 3 premières parties. Nous évaluerons le flot en termes de coûts dans la dernière partie, mais d’abord nous cherchons à faire passer un certain nombre d'unités de flots en fonction des capacités.

- **Question** : Qu’allez-vous utiliser pour marquer le fait qu’un arc n’existe pas dans la matrice sauvegardant les capacités ?
  
Pour marquer le fait qu’un arc n’existe pas dans la matrice sauvegardant les capacités, on peut simplement mettre des 0 cela montre que la capacité entre 2 sommets est nulle.

Nous allons tout d’abord reprendre un exemple du cours, celui où l’on cherchait à acheminer un maximum d’unités de flot (ici par exemple un nombre maximum d'objets) entre la ville de Stuttgart et Los Angeles. Nous avons trouvé ensemble que le flot maximal attendu était de 150 :

![Graphe Cours](/documents/images/grapheVille.png "Graphe Villes)

- **Question** : Représentez la matrice d’adjacence grapheEtCapacites pour cet exemple dans votre rapport. A vous d’identifier les indices pour reconnaître les villes associées (e.g., Stuttgart == 0 et Los Angeles == 6). On met de côté la matrice des coûts pour l’instant.

  Pour reconnaître les villes on leur donne des indices :
Stuttgart == 0, Rotterdam == 1, Bordeaux == 2, Lisbonne == 3, New York == 4, New Orleans == 5, Los Angeles == 6.

- **C++** : Utilisez soit un tableau 2D (type C), soit un double <vector>, soit un <array> afin d’enregistrer votre matrice d’adjacence grapheEtCapacites décrite à la question précédente.


On utilise ici un double vecteur d'entiers pour enregistrer la matrice d’adjacence grapheEtCapacites : 
On obtient cette sortie qui correspond bien à la matrice.

![Matrice Console]("Matrice Console")

Etape 2

Nous avons déjà vu en cours que l'efficacité de l’algorithme de Ford-Fulkerson dépendait principalement de la recherche du chemin améliorant. Un tel algorithme peut être basé sur un algorithme de parcours, et c’est, comme souvent, le parcours en largeur qui sera implémenté ici.

- **C++**. Nous allons maintenant nous attaquer à la boucle principale “Tant Que” de
  l’algorithme. Développez la, en vous basant sur le pseudo code suivant et en vous
  assurant ensuite de pouvoir récupérer le nouveau predDansCheminAmeliorant :



![Algo Parcours Longueur](/documents/images/algoParcoursLongueur.png "Algo Longueur")

Nous avons donc développé la fonction **parcoursLargeur** ci-dessous :

```C++


// Fonction du parcours en largeur
bool parcoursLargeur(const std::vector<std::vector<int>> &myGraph, int s, int t, std::vector<int> &predDansCheminAmeliorant)
{
  int n = myGraph.size(); // Nombre de sommets dans le graphe

  // Vecteur pour marquer les sommets visités
  std::vector<bool> sommetVisite(n, false);

  // File pour le parcours en largeur
  std::queue<int> file;

  // On enfile le sommet de départ s et on indique qu’il a été visité
  file.push(s);
  sommetVisite[s] = true;

  // Parcours en largeur
  while (!file.empty())
  {
    int u = file.front();
    file.pop();

    // Parcourir tous les sommets adjacents à u
    for (int v = 0; v < n; ++v)
    {
      // Si le sommet v n'est pas visité et il existe un arc (u, v) dans le graphe
      if (!sommetVisite[v] && myGraph[u][v] > 0)
      {
        // Marquer v comme visité
        sommetVisite[v] = true;
        // Ajouter v à la file
        file.push(v);
        // Enregistrer le prédécesseur de v
        predDansCheminAmeliorant[v] = u;
      }
    }
  }

  // Vérifier si t a été visité (existence d'un chemin reliant s à t)
  if (sommetVisite[t])
  {
    return true; // Un chemin reliant s à t existe
  }
  else
  {
    return false; // Aucun chemin reliant s à t n'existe
  }
}


```

**RAJOUTER STEP BY STEP PARCOURS LARGEUR**

Une fois ces étapes finit le code nous renvoie le parcours améliorant de façon optimisée, en effet nous lui donnons un graphe en paramètres et il nous renvoie son parcours améliorant. Pour vous donner un exemple voici le résultat obtenu quand nous exécutons le programme réalisé avec le graphe donné en énoncé : 

```bash

>>> Chemin améliorant de 0 à 6 : 0 -> 1 -> 4 -> 6

```

### Etape 3 : Algorithme de Ford-Fulkerson

Nous avons donc développé **parcoursLargeur** qui est une implémentation du parcours en
largeur adaptée pour renseigner de l’existence d’un chemin améliorant reliant un noeud s à
un noeud t. Nous allons maintenant développer l’algorithme de **Ford-Fulkerson** que l’on
note fordFulkerson.

- C++. Terminer l’implémentation de fordFulkerson. La dernière et principale partie de l’algorithme concerne la boucle Tant Que dont le pseudo-code est donné ci-dessous :

![algoFordFulkerson.png](/documents/images/algoFordFulkerson.png "algoFordFulkerson.png")



Nous avons donc développé la fonction **fordFulkerson** ci-dessous.
Elle prend en paramètre un graphe de capacité, les indices des sommets sources et puits.
Et elle renvoit le flot maximal de ce graphe :

```C++
// Fonction Ford-Fulkerson
int fordFulkerson(std::vector<std::vector<int>> &myGraph, int s, int t)
{
  int n = myGraph.size(); // Nombre de sommets dans le graphe

  // Créer le graphe résiduel initialisé avec les mêmes capacités que le graphe d'origine
  std::vector<std::vector<int>> grapheResiduel = myGraph;

  // Deux indices de sommets utilisés tout le long de l'algorithme
  int u, v;

  // Vecteur pour sauvegarder les prédécesseurs des sommets sur le chemin améliorant
  std::vector<int> predDansCheminAmeliorant(n, -1);

  // Initialiser le flot maximal à 0
  int max_flow = 0;

  // Boucle principale de l'algorithme
  while (parcoursLargeur(grapheResiduel, s, t, predDansCheminAmeliorant))
  {
    std::vector<int> cheminAmeliorant = reconstruireChemin(s, t, predDansCheminAmeliorant);
    for (auto &sommet : cheminAmeliorant)
    {
      std::cout << sommet << std::endl;
    }

    // Trouver la capacité résiduelle minimale le long du chemin améliorant

    // Initialisation du flot parcourant le chemin améliorant
    // Celui est initalisé à INT32_MAX, pour simuler une valeur "infinie"
    // ainsi, on est sûr qu'il n'y aura pas de problème lorsqu'il sera mis à jour en comparant sa valeur avec la capacité du chemin
    int ameliorationFlot = INT32_MAX;

    // Parcours chaque noeud v du chemin améliorant de t à s (dans l'autre sens)
    for (v = t; v != s; v = predDansCheminAmeliorant[v])
    {
      u = predDansCheminAmeliorant[v];
      ameliorationFlot = std::min(ameliorationFlot, grapheResiduel[u][v]);
    }

    // Ajouter le flot minimum trouvé au flot maximal
    max_flow += ameliorationFlot;

    std::cout << "fin de chemin |"
              << " flot max = " << max_flow << std::endl;

    // Mettre à jour les capacités résiduelles du graphe résiduel
    for (v = t; v != s; v = predDansCheminAmeliorant[v])
    {
      u = predDansCheminAmeliorant[v];
      grapheResiduel[u][v] -= ameliorationFlot; // Réduire la capacité sur l'arc direct
      grapheResiduel[v][u] += ameliorationFlot; // Ajouter de la capacité sur l'arc inverse (rétrogradation)                                // Remonter le chemin améliorant
    }
  }

  // Retourner le flot maximal
  return max_flow;
}
```

**RAJOUTER STEP BY STEP GRAPHE RESIDUEL**

### Etape 4 : Testez votre programme

- C++. Joignez les différentes parties de code développées en Partie 2 de façon à
retrouver un flot max de 150. Reportez la capture d’écran associée au résultat
obtenu à l’exécution de votre code.

En réunissant l'ensemble des fonctions développées dans la partie 2, on peut ainsi tester nos fonctions sur le graphe donné dans l'énoncé. 
Voici le retour console que l'on obtient :

```bash

0 -> 1 -> 4 -> 6 -> fin de chemin | flot max = 50
0 -> 2 -> 4 -> 6 -> fin de chemin | flot max = 80
0 -> 2 -> 5 -> 6 -> fin de chemin | flot max = 120
0 -> 3 -> 5 -> 6 -> fin de chemin | flot max = 150

```
Valeur flot max retournée : 150

On retrouve bien le flot maximal attendu.

## Problèmes réels

Partie 3 étape 1: faire les graphes flots et résiduels avec le flot infini

![Graphe Usine 1](/documents/images/grapheUsine1.png "Graphe Usine")