#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// Définition du type grapheEtCapacites
// On fait le choix d'utiliser un type double vector afin d'utiliser les fonctions associées

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

bool parcoursLargeur(const std::vector<std::vector<int>> &myGraph, int s, int t, std::vector<int> &predDansCheminAmeliorant)
{
  int n = myGraph.size(); // Nombre de sommets dans le graphe

  // Vecteur pour marquer les sommets visités
  std::vector<bool> visite(n, false);

  // File pour le parcours en largeur
  std::queue<int> file;

  // On enfile le sommet de départ s et on indique qu’il a été visité
  file.push(s);
  visite[s] = true;

  // Parcours en largeur
  while (!file.empty())
  {
    int u = file.front();
    file.pop();

    // Parcourir tous les sommets adjacents à u
    for (int v = 0; v < n; ++v)
    {
      // Si le sommet v n'est pas visité et il existe un arc (u, v) dans le graphe
      if (!visite[v] && myGraph[u][v] > 0)
      {
        // Marquer v comme visité
        visite[v] = true;
        // Ajouter v à la file
        file.push(v);
        // Enregistrer le prédécesseur de v
        predDansCheminAmeliorant[v] = u;
      }
    }
  }

  // Vérifier si t a été visité (existence d'un chemin reliant s à t)
  if (visite[t])
  {
    return true; // Un chemin reliant s à t existe
  }
  else
  {
    return false; // Aucun chemin reliant s à t n'existe
  }
}

// Fonction Ford-Fulkerson

/*
int fordFulkerson(graph &capacites, int s, int t)
{
  int n = capacites.size(); // Nombre de sommets dans le graphe

  // Créer le graphe résiduel initialisé avec les mêmes capacités que le graphe d'origine
  graph grapheResiduel = capacites;

  // Initialiser le flot maximal à 0
  int max_flow = 0;

  // Vecteur pour sauvegarder les prédécesseurs des sommets sur le chemin améliorant
  vector<int> predDansCheminAmeliorant(n, -1);

  // Boucle principale de l'algorithme
  while (parcoursLargeur(grapheResiduel, s, t, predDansCheminAmeliorant))
  {
    // Trouver la capacité résiduelle minimale le long du chemin améliorant
    int ameliorationFlot = INT_MAX;
    int v = t; // Initialiser v au puits t

    while (v != s)
    {
      int u = predDansCheminAmeliorant[v];
      ameliorationFlot = min(ameliorationFlot, grapheResiduel[u][v]);
      v = u; // Remonter le chemin améliorant
    }

    // Ajouter le flot minimum trouvé au flot maximal
    max_flow += ameliorationFlot;

    // Mettre à jour les capacités résiduelles du graphe résiduel
    v = t;
    while (v != s)
    {
      int u = predDansCheminAmeliorant[v];
      grapheResiduel[u][v] -= ameliorationFlot; // Réduire la capacité sur l'arc direct
      grapheResiduel[v][u] += ameliorationFlot; // Ajouter de la capacité sur l'arc inverse (rétrogradation)
      v = u;                                    // Remonter le chemin améliorant
    }
  }

  // Retourner le flot maximal
  return max_flow;
}
*/