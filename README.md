# Sujet TD&P n°5 - Séances n°7 et 8

![Junia Banner](/documents/images/junia_banner.jpeg "Junia Banner")

- [ ] Rajouter des "test" pour chaque utilisation de fonctions pour détailler le fonctionnement
- [ ] Essayer d'avoir des affichages détaillés pour chaque chemin améliorant
- [ ] Répondre aux questions et rajouter les écrans dans le rapport git

**Objectifs** : Comprendre, développer et expérimenter l’algorithme de Ford-Fulkerson sur les différentes situations proposées. Ce TD&P noté devrait mettre en valeur la puissance d’une modélisation d’un problème réel en un problème de flots dans un graphe. Au travers d’une application concrète, on cherche à satisfaire les consommations localisées d’un produit manufacturé selon la capacité de production, de transport, et de stockage de plusieurs usines de fabrication.

## Plan :

1. [Trace de l’algorithme de Ford-Fulkerson.](#trace-de-l'agorithme-de-Ford-Fulkerson)

2. [Implémentation de l’algorithme de parcours en largeur puis de l’algorithme de Ford-Fulkerson qui se servira du parcours.](#partie-2)

- [Étape 1 : Représentation mémoire du graphe][#Étape1]
- [Étape 2. Le parcours en largeur au service de la recherche du chemin améliorant.][#Étape2]

3. [Compréhension et modélisation de problèmes réels en graphes et recherche du flot maximum dans ces derniers. Les arcs des graphes supportent des capacités.](#problèmes-réels)

Partie 4. A vous de jouer sur l’écriture d’un algorithme qui va calculer le coût minimal d’un flot dont la valeur (i.e., le nombre d’unités) a déjà été calculée. Les arcs des graphes supportent des capacités et des coûts.

Bonus.

### Trace de l'agorithme de Ford-Fulkerson

### Partie 2

Etape 2

Nous avons déjà vu en cours que l'efficacité de l’algorithme de Ford-Fulkerson dépendait principalement de la recherche du chemin améliorant. Un tel algorithme peut être basé sur un algorithme de parcours, et c’est, comme souvent, le parcours en largeur qui sera implémenté ici.

- C++. Nous allons maintenant nous attaquer à la boucle principale “Tant Que” de
  l’algorithme. Développez la, en vous basant sur le pseudo code suivant et en vous
  assurant ensuite de pouvoir récupérer le nouveau predDansCheminAmeliorant :

![Algo Parcours Longueur](/docs/images/algoParcoursLongueur.png "Algo Longueur")

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

```

### Problèmes réels

Partie 3 étape 1: faire les graphes flots et résiduels avec le flot infini
