# Sujet TD&P n°5 - Séances n°7 et 8

![Junia Banner](/documents/images/junia_banner.jpeg "Junia Banner")

**Objectifs** : Comprendre, développer et expérimenter l’algorithme de Ford-Fulkerson sur les différentes situations proposées. Ce TD&P noté devrait mettre en valeur la puissance d’une modélisation d’un problème réel en un problème de flots dans un graphe. Au travers d’une application concrète, on cherche à satisfaire les consommations localisées d’un produit manufacturé selon la capacité de production, de transport, et de stockage de plusieurs usines de fabrication.

## Table de matière :

1. [Trace de l’algorithme de Ford-Fulkerson.](#trace-de-l'agorithme-de-Ford-Fulkerson)

2. [Implémentation de l’algorithme de parcours en largeur puis de l’algorithme de Ford-Fulkerson qui se servira du parcours.](#partie-2)

  - [Étape 1 : Représentation mémoire du graphe](#Étape1)
  - [Étape 2. Le parcours en largeur au service de la recherche du chemin améliorant.](#Étape2)

3. [Compréhension et modélisation de problèmes réels en graphes et recherche du flot maximum dans ces derniers. Les arcs des graphes supportent des capacités.](#problèmes-réels)

4. [A vous de jouer sur l’écriture d’un algorithme qui va calculer le coût minimal d’un flot dont la valeur (i.e., le nombre d’unités) a déjà été calculée. Les arcs des graphes supportent des capacités et des coûts.](#Partie4)

5. [Bonus.](#Bonus)

## Partie 1 

- **Trace**. On va tout d’abord s’exercer “à la main” sur un exemple simple. Déroulez
l’algorithme de Ford-Fulkerson sur l’exemple ci-dessous afin de calculer le flot max
entre les sommets s et t. Votre rapport doit contenir chaque étape de la trace :
  - une étape correspond ici à une itération de la boucle “Tant Que” où il faut
  faire apparaître le graphe résiduel ET le graphe des flots et en mettant en
  évidence chaque nouveau chemin améliorant et enfin l’absence de celui-ci
  pour sortir de l’algorithme.


![Graphe Partie 1](/documents/images/graphePartie1.png "Partie 1")

Etant donné qu’il n’est plus possible de trouver de chemin améliorant à cause des arcs saturés, on peut voir que le flot maximal est de **19**.

La somme des flots sortants du la source **s : 9 + 10**
La somme des flots entrants dans le puits **t : 10 + 9**




## Partie 2

**Etape 1**

Nous allons tout d’abord enregistrer un graphe en mémoire avec les techniques vues en cours.

- **Question** : Quelle matrice est donnée en exemple dans le cours pour à la fois enregistrer l’existence d’un arc mais aussi leur poids (i.e., leur coût).

La matrice donnée dans le cours qui permet de représenter un graphe est la matrice d’adjacence notée **Madj** :

![Matrice Adjacence](/documents/images/matriceAdjacence.png "Matrice Adjacence")

- **Question** : Expliquez l’intérêt des coûts infinis dans une telle matrice.
  
L’intérêt des coûts infinis dans une telle matrice est de représenter l’absence de liaison entre 2 sommets. Dans les algorithmes de recherche de chemin comme Dijkstra ou Bellman-Ford, les coûts infinis sont utilisés pour indiquer des chemins non parcourables ou des chemins qui n'existent pas.

Nous allons utiliser 2 matrices du même type pour sauvegarder les informations d’un graphe. L’une enregistrera les capacités, l’autre les coûts de chaque arc. La matrice des coûts ne sera utilisée qu’en partie 4 : nous travaillerons d’abord sur la matrice des capacités puisque le gros du travail consistera à trouver un flot max dans les 3 premières parties. Nous évaluerons le flot en termes de coûts dans la dernière partie, mais d’abord nous cherchons à faire passer un certain nombre d'unités de flots en fonction des capacités.

- **Question** : Qu’allez-vous utiliser pour marquer le fait qu’un arc n’existe pas dans la matrice sauvegardant les capacités ?
  
Pour marquer le fait qu’un arc n’existe pas dans la matrice sauvegardant les capacités, on peut simplement mettre des 0 cela montre que la capacité entre 2 sommets est nulle.

Nous allons tout d’abord reprendre un exemple du cours, celui où l’on cherchait à acheminer un maximum d’unités de flot (ici par exemple un nombre maximum d'objets) entre la ville de Stuttgart et Los Angeles. Nous avons trouvé ensemble que le flot maximal attendu était de 150 :

![Graphe Cours](/documents/images/grapheVilles.png "Graphe Villes")

- **Question** : Représentez la matrice d’adjacence **grapheEtCapacites** pour cet exemple dans votre rapport. A vous d’identifier les indices pour reconnaître les villes associées (e.g., Stuttgart == 0 et Los Angeles == 6). On met de côté la matrice des coûts pour l’instant.

  Pour reconnaître les villes on leur donne des indices :
- Stuttgart == 0,
- Rotterdam == 1,
- Bordeaux == 2,
- Lisbonne == 3,
- New York == 4,
- New Orleans == 5,
- Los Angeles == 6.

|   | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|---|---|
| 0 | 0 | 50| 70| 40| 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 0 | 60| 0 | 0 |
| 2 | 0 | 0 | 0 | 0 | 40| 50| 0 |
| 3 | 0 | 0 | 0 | 0 | 0 | 30| 0 |
| 4 | 0 | 0 | 0 | 0 | 0 | 0 | 80|
| 5 | 0 | 0 | 0 | 0 | 0 | 0 | 70|
| 6 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

Cette matrice se lit des lignes vers les colonnes, ainsi l'arc de 1 vers 4 (Rotterdam -> New York) nous donne 60 de capacité.

- **C++** : Utilisez soit un tableau 2D (type C), soit un double vector, soit un array afin d’enregistrer votre matrice d’adjacence grapheEtCapacites décrite à la question précédente.

On utilise ici un double vecteur d'entiers pour enregistrer la matrice d’adjacence grapheEtCapacites : 
On obtient cette sortie qui correspond bien à la matrice.

```C++

  // Définition du type de notre matrice d'adjacence
  using grapheType = std::vector<std::vector<int>>;


  // Initialisation de la matrice d'adjacence grapheEtCapacites
  // On fait le choix d'utiliser un type double vector afin d'utiliser les fonctions associées

  grapheType grapheEtCapacites = {
      {0, 50, 70, 40, 0, 0, 0}, // Stuttgart (0)
      {0, 0, 0, 0, 60, 0, 0},   // Rotterdam (1)
      {0, 0, 0, 0, 40, 50, 0},  // Bordeaux (2)
      {0, 0, 0, 0, 0, 30, 0},   // Lisbon (3)
      {0, 0, 0, 0, 0, 0, 80},   // New York (4)
      {0, 0, 0, 0, 0, 0, 70},   // New Orleans (5)
      {0, 0, 0, 0, 0, 0, 0}     // Los Angeles (6)
  };

// On affiche le graphe en console à l'aide de notre fonction displayMadj
displayMadj(

```

```bash

>>> Matrice d'ajdacence du graphe : 

0 | 50 | 70 | 40 |  0 |  0 |  0 | 
0 |  0 |  0 |  0 | 60 |  0 |  0 | 
0 |  0 |  0 |  0 | 40 | 50 |  0 | 
0 |  0 |  0 |  0 |  0 | 30 |  0 | 
0 |  0 |  0 |  0 |  0 |  0 | 80 | 
0 |  0 |  0 |  0 |  0 |  0 | 70 | 
0 |  0 |  0 |  0 |  0 |  0 |  0 | 

```

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

Une fois ces étapes finit le code nous renvoie le parcours améliorant de façon optimisée, en effet nous lui donnons un graphe en paramètres et il nous renvoie son parcours améliorant. Pour vous donner un exemple voici le résultat obtenu quand nous exécutons le programme réalisé avec le graphe donné en énoncé : 

```bash

>>> Chemin améliorant de 0 à 6 : 0 -> 1 -> 4 -> 6

```

### Etape 3 : Algorithme de Ford-Fulkerson

Nous avons donc développé la fonction**parcoursLargeur** qui est une implémentation du parcours en
largeur adaptée pour renseigner de l’existence d’un chemin améliorant reliant un noeud s à
un noeud t. Nous allons maintenant développer l’algorithme de **Ford-Fulkerson** que l’on
note fordFulkerson.

- **C++**. Terminer l’implémentation de fordFulkerson. La dernière et principale partie de l’algorithme concerne la boucle Tant Que dont le pseudo-code est donné ci-dessous :

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
Cette fonction renvoit le flot maximal du graphe donné en entrée. 

### Etape 4 : Testez votre programme

- **C++**. Joignez les différentes parties de code développées en Partie 2 de façon à
retrouver un flot max de 150. Reportez la capture d’écran associée au résultat
obtenu à l’exécution de votre code.

En réunissant l'ensemble des fonctions développées dans la partie 2, on peut ainsi tester nos fonctions sur le graphe donné dans l'énoncé. 
Voici le retour console que l'on obtient :

```bash

>>> 0 -> 1 -> 4 -> 6 -> fin de chemin | flot max = 50
>>> 0 -> 2 -> 4 -> 6 -> fin de chemin | flot max = 80
>>> 0 -> 2 -> 5 -> 6 -> fin de chemin | flot max = 120
>>> 0 -> 3 -> 5 -> 6 -> fin de chemin | flot max = 150

```
Valeur flot max retournée : 150

On retrouve bien le flot maximal attendu.

On peut également essayer la fonction fordFulkerson sur le graphe qu'on a itéré à la main dans la partie 1 : 

```C++

  grapheType graphePartie1 = {
      {0, 10, 10, 0, 0, 0}, // sommet s
      {0, 0, 2, 4, 8, 0},   // sommet a
      {0, 0, 0, 0, 9, 0},   // sommet b
      {0, 0, 0, 0, 0, 10},  // sommet c
      {0, 0, 0, 6, 0, 10},  // sommet d
      {0, 0, 0, 0, 0, 0},   // sommet t
  };

  s = 0;
  t = 5;

  if (!DISPLAY)
  {
    std::cout << fordFulkerson(graphePartie1, s, t) << std::endl;
  }
```
```bash

>>> Flot maximal du graphe : 19
```
Cela retourne bien le même résultat trouvé à la main ultérieurement. 

## Problèmes réels

Partie 3 étape 1: faire les graphes flots et résiduels avec le flot infini

Imaginez avoir la responsabilité d’une société disposant de 3 usines produisant des tonnes
de tablettes de chocolat9, chacune dans un pays différent. Pour chaque pays i, il y a une
consommation (demande) associée Dem(i). Dans l’exemple ci-dessous, on demande à
l’usine Belge de fournir 7 unités, la française 20 unités et la Suisse 5 unités. On considère
ici que chaque unité de flot correspond à une unité de chocolat.

![Graphe Usine 1](/documents/images/grapheUsine1.png "Graphe Usine")

- **C++**. Représentez ce nouveau graphe en mémoire et liez-le au code écrit dans la
partie précédente en y incluant la demande. A vous de réfléchir à quoi faire pour
modéliser les arcs de production avec les différentes techniques vues en cours,
puisqu’il n’y a pas, pour l’instant, de limitation sur la capacité de production.

Pour modéliser les arcs de productions qui pour l'instant n'ont pas de capacités de production, on a décidé de leur assigné une valeur "infinie". 
La valeur numérique **INT32_MAX** représente le plus grand nombre entier en 32 bits, ce qui suffira pour simuler une infinité :

```C++

  int demFrance = 19;
  int demBelgique = 7;
  int demSuisse = 5;

  grapheType grapheUsine = {
      {0, INT32_MAX, INT32_MAX, INT32_MAX, 0},
      {0, 0, 0, 0, demFrance},
      {0, 0, 0, 0, demBelgique},
      {0, 0, 0, 0, demSuisse},
      {0, 0, 0, 0, 0},
  };

  s = 0; // Noeud de départ
  t = 4; // Noeud d'arrivée
```

- **C++**. Exécutez alors Ford-Fulkerson sur ce graphe, puis faites ressortir le flot max.
Faites une capture d’écran du résultat de votre sortie terminal (IDE ou
console) pour l’insérer dans votre rapport.

```C++

  int flotMax = fordFulkerson(grapheUsine, s, t);

  std::cout << "Le flot maximal pour ce premier graphe est : " << flotMax << std::endl;

```
On obtient ainsi en console le résultat suivant : 

```bash 
>>> Le flot maximal pour ce premier graphe est : 31
```

- **Représentation de Graphe**. A partir de la situation précédente, mettez à jour le
graphe donné plus haut en y ajoutant les capacités de production du tableau
ci-dessous. Réfléchissez à l'endroit où interviennent ces capacités. Reportez votre
dessin dans votre rapport. Vous êtes libres du choix de l’outil pour le dessiner.

On peut ainsi modéliser les capacités de productions sur les arcs 1>2, 1>3, 1>4 qui n'étaient pas définis avant :

![Graphe Usine 2](/documents/images/grapheUsine2.png "Graphe Usine2")

- **C++**. Adaptez votre code avec les capacités de production données par le tableau
précédent, exécutez le, et enfin reportez les captures d’écran du résultat obtenu.

```C++

  int capProdFrance = 25;
  int capProdBelgique = 10;
  int capProdSuisse = 8;

  grapheUsine = {
      {0, capProdFrance, capProdBelgique, capProdSuisse, 0}, // sommet 1
      {0, 0, 0, 0, demFrance},                               // sommet 2
      {0, 0, 0, 0, demBelgique},                             // sommet 3
      {0, 0, 0, 0, demSuisse},                               // sommet 4
      {0, 0, 0, 0, 0},                                       // sommet 5
  };

  int flotMax = fordFulkerson(grapheUsine, s, t);

  if (DISPLAY)
  {
    std::cout << "Le flot maximal pour ce deuxième graphe est : " << flotMax << std::endl;
  }
```
```bash
>>> Le flot maximal pour ce deuxième graphe est : 31
```

On constate qu'en rajoutant les capacités de productions, on obtient le même flot maximal qu'à la question précédente. 

**Etape 3**

On ajoute maintenant la possibilité de transférer les unités de chocolat entre les usines une
fois celles-ci produites. Les transferts d’unité de chocolat peuvent être considérés comme
instantanés et suivant le processus de production.
Les camions ou autres moyens de transport sont en nombre limité, on considère une
capacité sur ces transferts que l’on notera CapTrans. Ainsi, si i et j sont deux une usine,
la capacité de transfert de l’usine i vers l’usine j est notée CapTrans(i>j).

![Graphe Usine 3](/documents/images/grapheUsine3.png "Graphe Usine Partie 3")

- **C++**. Adaptez votre code précédent à ces capacités de transfert et cette nouvelle
demande, exécutez le, et enfin reportez les captures d’écran du résultat obtenu dans
votre rendu.

```C++

  demFrance = 30;
  int capTransFB = 8;
  int capTransBF = 8;
  int capTransBS = 3;
  int capTransSB = 3;
  int capTransFS = 12;
  int capTransSF = 12;

  grapheUsine = {
      {0, 25, 10, 8, 0},
      {0, 0, capTransFB, capTransFS, demFrance},
      {0, capTransBF, 0, capTransBS, demBelgique},
      {0, capTransSF, capTransSB, 0, demSuisse},
      {0, 0, 0, 0, 0},
  };

  flotMax = fordFulkerson(grapheUsine, s, t);

  if (DISPLAY)
  {
    std::cout << "Le flot maximal pour ce troisième graphe est : " << flotMax << std::endl;
  }
```
```bash

>>> Le flot maximal pour ce troisième graphe est : 42
```

En rajoutant les capacités de transfert, on obtient un flot maximal plus important.

**Etape 4**

Nous allons maintenant considérer plusieurs périodes de temps afin de pouvoir stocker les
produits d’une période à l’autre et ceci dans chaque pays. Cela permet de nouvelles
possibilités pour satisfaire la demande.
Reprenons le même exemple avec nos trois usines mais cette fois avec la possibilité de
stocker des d’unités de chocolat produites. Nous allons voir comment représenter ces
périodes. Pour cela, “clonons” chaque sommet “usine” de façon à avoir un sommet par pays
et par période de temps. Si on considère deux périodes de temps t1 et t2, nous avons les
sommets suivants :
- (2.1) et (2.2) : respectivement l’usine en France pour les périodes 1 et 2 ;
- (3.1) et (3.2) : respectivement l’usine en Belgique pour les périodes 1 et 2 ;
- (4.1) et (4.2) : respectivement l’usine en Suisse pour les périodes 1 et 2.

On considère le stockage comme un processus démarrant après la production et les
transferts de la période donnée. Ceci devrait se faire de manière transparente si vous
respectez les caractéristiques des graphes présentés ici.

Si i est une usine, t1 et t2 deux périodes de stockage consécutives, le stockage d’unité
de chocolat de la période t1 à la période t2 de l’usine i consomme une unité de capacité
notée CapStock(i.t1).

- **Représentation de Graphe**. En vous aidant de la figure ci-dessous qui ne
représente que les capacités de production et de stockage d’un seul pays, dessinez
le graphe “global” pour toutes les capacités (production, stockage et transfert), ainsi
que la demande. Vous pouvez vous limiter à deux pays que vous aurez choisis.

![Graphe Usine 4](/documents/images/grapheUsine4.png "Graphe Usine Partie 4")

On obtient ainsi le graphe ci-dessus qui est très conséquent par le nombre d'arcs de production, stockages, transferts et demandes. 

- **C++**. Adaptez votre code pour le problème avec toutes les capacités (production,
transfert et stockage) appliquées aux 3 pays en reprenant les valeurs des tableaux
ci-dessus. Exécutez ensuite votre programme et reportez les captures d’écran du
résultat obtenu.

```C++

  // On rajoute des sommets

  s = 0; // Noeud de départ
  t = 7; // Noeud d'arrivée

  // Définition de tous les arcs pour la France
  int capProdFrance1 = 25;
  int capProdFrance2 = 15;
  int capStockFrance = 15;
  int capTransFB1 = 10;
  int capTransFB2 = 5;
  int capTransFS1 = 10;
  int capTransFS2 = 5;
  int demFrance1 = 14;
  int demFrance2 = 19;

  // Définition de tous les arcs pour la Belgique
  int capProdBelgique1 = 10;
  int capProdBelgique2 = 5;
  int capStockBelgique = 8;
  int capTransBF1 = 4;
  int capTransBF2 = 8;
  int capTransBS1 = 10;
  int capTransBS2 = 5;
  int demBelgique1 = 3;
  int demBelgique2 = 10;

  // Définition de tous les arcs pour la Suisse
  int capProdSuisse1 = 5;
  int capProdSuisse2 = 8;
  int capStockSuisse = 7;
  int capTransSB1 = 10;
  int capTransSB2 = 5;
  int capTransSF1 = 4;
  int capTransSF2 = 7;
  int demSuisse1 = 7;
  int demSuisse2 = 5;

  grapheUsine = {
      {0, capProdFrance1, capProdFrance2, capProdBelgique1, capProdBelgique2, capProdSuisse1, capProdSuisse2, 0}, // sommet s
      {0, 0, capStockFrance, capTransFB1, 0, capTransFS1, 0, demFrance1},                                         // sommet France t1
      {0, 0, 0, 0, capTransFB2, 0, capTransFS2, demFrance2},                                                      // sommet France t2
      {0, capTransBF1, 0, 0, capStockBelgique, capTransBS1, 0, demBelgique1},                                     // sommet Belgique t1
      {0, 0, capTransBF2, 0, 0, 0, capTransBS2, demBelgique2},                                                    // sommet Belgique t2
      {0, capTransSF1, 0, capTransSB1, 0, 0, capStockSuisse, demSuisse1},                                         // sommet Suisse t1
      {0, 0, capTransSF2, 0, capTransSB2, 0, 0, demSuisse2},                                                      // sommet Suisse t2
      {0, 0, 0, 0, 0, 0, 0, 0},                                                                                   // sommet t
  };

  flotMax = fordFulkerson(grapheUsine, s, t);

  if (!DISPLAY)
  {
    std::cout << "Le flot maximal pour ce quatrième graphe est : " << flotMax << std::endl;
  }
```
```bash
>>> Le flot maximal pour ce quatrième graphe est : 58
```

**Etape 5**

Pour anticiper (ou pas) une période troublée, vous essayez d’évaluer la robustesse de votre
système de production devant une demande variable.

- **C++**. En vous basant sur les travaux de l’étape précédente, adaptez votre code de
façon à considérer des demandes générées aléatoirement14 mais dont les valeurs,
inférieures ou supérieures, restent assez proches des valeurs initiales (à vous de
choisir une borne Min et une borne Max pour chacune des demandes et indiquez-les
dans votre rapport). Relevez le résultat obtenu accompagné de la demande générée
à travers une copie écran du résultat de la console.

Dans un premier temps nous avons implémenté notre moteur de génération de nombres aléatoires

```C++

  // Calcul de la graine basée sur le nombre de lettres dans nos prénoms
  int mySeed = 6 + 5 + 7 + 6 + 7; // = 31

  // Moteur de nombres aléatoires initialisé avec la graine
  std::mt19937 gen(mySeed);

  // Distribution pour des nombres entre 1 et 25
  std::uniform_int_distribution<> dis(-10, 10);

```

La graine de notre générateur est basée sur la somme du nombre de lettres dans chacun de nos prénoms.
Ainsi, on modifie les demandes dans notre graphe actuel : 

```C++

  // Génération des nombres aléatoires
  demFrance1 = 15 + dis(gen);
  demFrance2 = 15 + dis(gen);
  demBelgique1 = 15 + dis(gen);
  demBelgique2 = 15 + dis(gen);
  demSuisse1 = 15 + dis(gen);
  demSuisse2 = 15 + dis(gen);

  grapheUsine = {
      {0, capProdFrance1, capProdFrance2, capProdBelgique1, capProdBelgique2, capProdSuisse1, capProdSuisse2, 0}, // sommet s
      {0, 0, capStockFrance, capTransFB1, 0, capTransFS1, 0, demFrance1},                                         // sommet France t1
      {0, 0, 0, 0, capTransFB2, 0, capTransFS2, demFrance2},                                                      // sommet France t2
      {0, capTransBF1, 0, 0, capStockBelgique, capTransBS1, 0, demBelgique1},                                     // sommet Belgique t1
      {0, 0, capTransBF2, 0, 0, 0, capTransBS2, demBelgique2},                                                    // sommet Belgique t2
      {0, capTransSF1, 0, capTransSB1, 0, 0, capStockSuisse, demSuisse1},                                         // sommet Suisse t1
      {0, 0, capTransSF2, 0, capTransSB2, 0, 0, demSuisse2},                                                      // sommet Suisse t2
      {0, 0, 0, 0, 0, 0, 0, 0},                                                                                   // sommet t
  };
```
Enfin, on re-applique l'algorithme de Ford-Fulkerson afin de déterminer le nouveau flot maximal. 

```C++
  flotMax = fordFulkerson(grapheUsine, s, t);

  if (!DISPLAY)
  {
    std::cout << "Le flot maximal pour ce cinquième graphe est : " << flotMax << std::endl;
  }
```
```bash
>>> Le flot maximal pour ce cinquième graphe est : 68
```

En considérant des périodes de 15 jours (T1 et T2 formant un mois), on peut simuler ce que
le système de production est capable de supporter sur une année. Ici chaque mois est
indépendant.

- **C++**. Modifiez votre code de façon à itérer 12 fois sur la recherche du flot maximum
et où la demande aura changé autant de fois et selon les règles de la question
précédente. Formater l’affichage du résultat (flot max) obtenu sur le terminal de
façon à faire apparaître, pour chacune des 12 itérations :
- la demande aléatoire générée (pour chaque arc),
- le pourcentage de la demande satisfaite pour chaque mois,
Relevez enfin le pourcentage de la demande satisfaite sur l’année. Reportez des
copies-écrans de ces résultats dans votre rapport.

```C++

  for (int i = 1; i <= 12; i++)
  {
    demFrance1 = 15 + dis(gen);
    demFrance2 = 15 + dis(gen);
    demBelgique1 = 15 + dis(gen);
    demBelgique2 = 15 + dis(gen);
    demSuisse1 = 15 + dis(gen);
    demSuisse2 = 15 + dis(gen);

    grapheUsine = {
        {0, capProdFrance1, capProdFrance2, capProdBelgique1, capProdBelgique2, capProdSuisse1, capProdSuisse2, 0}, // sommet s
        {0, 0, capStockFrance, capTransFB1, 0, capTransFS1, 0, demFrance1},                                         // sommet France t1
        {0, 0, 0, 0, capTransFB2, 0, capTransFS2, demFrance2},                                                      // sommet France t2
        {0, capTransBF1, 0, 0, capStockBelgique, capTransBS1, 0, demBelgique1},                                     // sommet Belgique t1
        {0, 0, capTransBF2, 0, 0, 0, capTransBS2, demBelgique2},                                                    // sommet Belgique t2
        {0, capTransSF1, 0, capTransSB1, 0, 0, capStockSuisse, demSuisse1},                                         // sommet Suisse t1
        {0, 0, capTransSF2, 0, capTransSB2, 0, 0, demSuisse2},                                                      // sommet Suisse t2
        {0, 0, 0, 0, 0, 0, 0, 0},                                                                                   // sommet t
    };

    

    flotMax = fordFulkerson(grapheUsine, s, t);

    if (DISPLAY)
    {
      std::cout << "Mois n°" << i << " Le flot maximal pour ce cinquième graphe est : " << flotMax << std::endl;
    }
  }
```
```bash
Mois n°1 Le flot maximal pour ce cinquième graphe est : 68
Mois n°2 Le flot maximal pour ce cinquième graphe est : 68
Mois n°3 Le flot maximal pour ce cinquième graphe est : 66
Mois n°4 Le flot maximal pour ce cinquième graphe est : 67
Mois n°5 Le flot maximal pour ce cinquième graphe est : 59
Mois n°6 Le flot maximal pour ce cinquième graphe est : 68
Mois n°7 Le flot maximal pour ce cinquième graphe est : 68
Mois n°8 Le flot maximal pour ce cinquième graphe est : 68
Mois n°9 Le flot maximal pour ce cinquième graphe est : 68
Mois n°10 Le flot maximal pour ce cinquième graphe est : 68
Mois n°11 Le flot maximal pour ce cinquième graphe est : 68
Mois n°12 Le flot maximal pour ce cinquième graphe est : 61
```

Sur une année, le flot max ne change pas énormément. Le plus gros écart par rapport au flot maximal initial trouvé est de 9. 




**Partie 4**

- **C++**. Génération des coûts. On va tout d’abord chercher à générer l’ensemble des
coûts 𝑐(𝑖, 𝑗), 𝑖, 𝑗 ∈ 𝑋, pour tous les arcs qui ne sont pas des arcs de demande :
- les coûts de stockage,
- les coûts de transfert,
- les coûts de production.
Générez des coûts différents pour chaque type d’arc (production, transfert et
stockage) et cela pour chacun des pays en vous aidant de la génération de nombres
pseudo-aléatoires. Ainsi, servez-vous d’une matrice de la même taille que
grapheEtCapacites, mais cette fois pour sauvegarder les coûts générés. Relever le
graphe des coûts que vous obtenez dans votre rapport.

```C++
// Définition de tous les arcs pour la France
  capProdFrance1 = dis(gen);
  capProdFrance2 = dis(gen);
  capStockFrance = dis(gen);
  capTransFB1 = dis(gen);
  capTransFB2 = dis(gen);
  capTransFS1 = dis(gen);
  capTransFS2 = dis(gen);
  demFrance1 = dis(gen);
  demFrance2 = dis(gen);

  // Définition de tous les arcs pour la Belgique
  capProdBelgique1 = dis(gen);
  capProdBelgique2 = dis(gen);
  capStockBelgique = dis(gen);
  capTransBF1 = dis(gen);
  capTransBF2 = dis(gen);
  capTransBS1 = dis(gen);
  capTransBS2 = dis(gen);
  demBelgique1 = dis(gen);
  demBelgique2 = dis(gen);

  // Définition de tous les arcs pour la Suisse
  capProdSuisse1 = dis(gen);
  capProdSuisse2 = dis(gen);
  capStockSuisse = dis(gen);
  capTransSB1 = dis(gen);
  capTransSB2 = dis(gen);
  capTransSF1 = dis(gen);
  capTransSF2 = dis(gen);
  demSuisse1 = dis(gen);
  demSuisse2 = dis(gen);

  grapheType grapheUsineCout = {
      {0, capProdFrance1, capProdFrance2, capProdBelgique1, capProdBelgique2, capProdSuisse1, capProdSuisse2, 0}, // sommet s
      {0, 0, capStockFrance, capTransFB1, 0, capTransFS1, 0, 0},                                                  // sommet France t1
      {0, 0, 0, 0, capTransFB2, 0, capTransFS2, 0},                                                               // sommet France t2
      {0, capTransBF1, 0, 0, capStockBelgique, capTransBS1, 0, 0},                                                // sommet Belgique t1
      {0, 0, capTransBF2, 0, 0, 0, capTransBS2, 0},                                                               // sommet Belgique t2
      {0, capTransSF1, 0, capTransSB1, 0, 0, capStockSuisse, 0},                                                  // sommet Suisse t1
      {0, 0, capTransSF2, 0, capTransSB2, 0, 0, 0},                                                               // sommet Suisse t2
      {0, 0, 0, 0, 0, 0, 0, 0},                                                                                   // sommet t
  };

  if (DISPLAY)
  {
    displayMadj(grapheUsineCout);
  }
```
```bash
>>> Matrice d'ajdacence du graphe : 
0 | 17 |  4 |  5 |  2 | 10 | 17 | 0 | 
0 |  0 |  3 | 26 |  0 | 18 |  0 | 0 | 
0 |  0 |  0 |  0 | 12 |  0 | 21 | 0 | 
0 |  7 |  0 |  0 | 23 | 14 |  0 | 0 | 
0 |  0 | 31 |  0 |  0 |  0 |  4 | 0 | 
0 |  2 |  0 | 15 |  0 |  0 | 30 | 0 | 
0 |  0 |  9 |  0 |  9 |  0 |  0 | 0 | 
0 |  0 |  0 |  0 |  0 |  0 |  0 | 0 |
```

- **C++**. Partie libre. Modifiez votre code de l'algorithme de Ford Fulkerson de façon à
pouvoir calculer le coût d’une solution. Ainsi, il faut trouver ici un moyen de déduire le
parcours des unités de flots.
Ensuite, trouvez une manière de calculer le coût total pour faire la somme des
produits des coûts de chaque arc par le nombre des unités de flots qui le traverse.

```C++

// Fonction Ford-Fulkerson Coût
int fordFulkersonCost(grapheType &myGraph, grapheType &myCostGraph, int s, int t)
{
  int n = myGraph.size(); // Nombre de sommets dans le graphe

  // Créer le graphe résiduel initialisé avec les mêmes capacités que le graphe d'origine
  grapheType grapheResiduel = myGraph;

  // Deux indices de sommets utilisés tout le long de l'algorithme
  int u, v;

  // Vecteur pour sauvegarder les prédécesseurs des sommets sur le chemin améliorant
  std::vector<int> predDansCheminAmeliorant(n, -1);

  // Initialiser le flot maximal à 0
  int max_flow = 0;
  int totalCost = 0;

  // Boucle principale de l'algorithme
  while (parcoursLargeur(grapheResiduel, s, t, predDansCheminAmeliorant))
  {
    std::vector<int> cheminAmeliorant = reconstruireChemin(s, t, predDansCheminAmeliorant);
    for (auto &sommet : cheminAmeliorant)
    {
      if (DISPLAY)
      {
        std::cout << sommet << " -> ";
      }
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
      totalCost += myCostGraph[u][v] * ameliorationFlot;
      if (DISPLAY)
      {
        std::cout << "cost : " << totalCost << std::endl;
      }
    }

    // Ajouter le flot minimum trouvé au flot maximal
    max_flow += ameliorationFlot;
    if (DISPLAY)
    {
      std::cout << "fin de chemin |"
                << " flot max = " << max_flow << std::endl;
    }
    // Mettre à jour les capacités résiduelles du graphe résiduel
    for (v = t; v != s; v = predDansCheminAmeliorant[v])
    {
      u = predDansCheminAmeliorant[v];
      grapheResiduel[u][v] -= ameliorationFlot; // Réduire la capacité sur l'arc direct
      grapheResiduel[v][u] += ameliorationFlot; // Ajouter de la capacité sur l'arc inverse (rétrogradation)                                // Remonter le chemin améliorant
    }
  }

  // Retourner le flot maximal
  return max_flow, totalCost;
}
```



**Algo**. Partie libre. Imaginez, puis écrire l’algorithme cherchant : soit le planning le
moins coûteux, soit un des moins coûteux pour un flot max déjà calculé ; ceci
correspond respectivement à écrire soit une méthode exacte, soit une méthode
approchée18. Que vous fassiez le premier ou le second choix, prenez le temps de
bien expliquer votre algorithme dans votre rapport.

Dans un premier temps, nous allons expérimenter des tests sur des graphes avec moins de sommets que le dernier que l'on vient de faire ci-dessus. 


** Pour n répétitions 
    chercher un chemin avec un coût moindre 

