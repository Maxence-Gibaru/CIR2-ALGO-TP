#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "config.hpp"

// Définition du type de notre matrice d'adjacence
using grapheType = std::vector<std::vector<int>>;

void displayMadj(grapheType &myGraph)
{
  std::cout << "Matrice d'ajdacence du graphe : " << std::endl;
  for (int i = 0; i < myGraph.size(); i++)
  {
    for (int j = 0; j < myGraph.size(); j++)
    {
      std::cout << myGraph[i][j] << " | ";
    }
    std::cout << std::endl;
  }
}

// Fonction pour reconstruire le chemin améliorant à partir de predDansCheminAmeliorant
std::vector<int> reconstruireChemin(int s, int t, const std::vector<int> &predDansCheminAmeliorant)
{
  std::vector<int> chemin;
  int sommetCourant = t;
  chemin.push_back(sommetCourant);

  while (sommetCourant != s)
  {
    sommetCourant = predDansCheminAmeliorant[sommetCourant];
    chemin.push_back(sommetCourant);
  }

  reverse(chemin.begin(), chemin.end()); // Inverser le chemin pour obtenir s --> t
  return chemin;
}

// Fonction du parcours en largeur
bool parcoursLargeur(const grapheType &myGraph, int s, int t, std::vector<int> &predDansCheminAmeliorant)
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

// Fonction Ford-Fulkerson
int fordFulkerson(grapheType &myGraph, int s, int t)
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
  return max_flow;
}

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
  return max_flow;
}


// Fonction pour trouver le planning le moins coûteux pour un flot maximal donné
int findMinCostForMaxFlow(grapheType &myGraph, grapheType &myCostGraph, int s, int t, int max_flow)
{
  int low = 0;          // Initialisation de la borne inférieure
  int high = INT32_MAX; // Initialisation de la borne supérieure

  while (high - low > 0.001)
  {                             // Tant que la différence entre low et high est significative
    int mid = (low + high) / 2; // Calcul du coût moyen

    // Modifiez les capacités des arcs du graphe résiduel en fonction de mid
    grapheType grapheResiduel = myGraph;
    for (int i = 0; i < grapheResiduel.size(); ++i)
    {
      for (int j = 0; j < grapheResiduel[i].size(); ++j)
      {
        if (myCostGraph[i][j] <= mid)
        {
          grapheResiduel[i][j] = myGraph[i][j]; // Garder la capacité originale
        }
        else
        {
          grapheResiduel[i][j] = 0; // Réduire la capacité à zéro pour les arcs ayant un coût supérieur à mid
        }
      }
    }

    // Utilisation de l'algorithme de Ford-Fulkerson pour trouver le flot maximal
    int current_flow = fordFulkerson(grapheResiduel, s, t);

    // Mise à jour des bornes en fonction du résultat de l'algorithme de Ford-Fulkerson
    if (current_flow == max_flow)
    {
      high = mid;
    }
    else
    {
      low = mid;
    }
  }

  // Retourner le coût minimal trouvé
  return high;
}
