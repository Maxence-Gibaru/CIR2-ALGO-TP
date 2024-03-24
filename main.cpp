#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Définition du type grapheEtCapacites
// On fait le choix d'utiliser un type double vector afin d'utiliser les fonctions associées
using graph = vector<vector<int>>;

// Fonction pour reconstruire le chemin améliorant à partir de predDansCheminAmeliorant
vector<int> reconstruireChemin(int s, int t, const vector<int> &predDansCheminAmeliorant)
{
  vector<int> chemin;
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

bool parcoursLargeur(const graph &myGraph, int s, int t, vector<int> &predDansCheminAmeliorant)
{
  int n = myGraph.size(); // Nombre de sommets dans le graphe

  // Vecteur pour marquer les sommets visités
  vector<bool> visite(n, false);

  // File pour le parcours en largeur
  queue<int> file;

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

int main()
{

  // Partie 2 étape 1
  // Initialisation de la matrice d'adjacence grapheEtCapacites
  graph grapheEtCapacites = {
      {0, 50, 70, 40, 0, 0, 0}, // Stuttgart (0)
      {0, 0, 0, 0, 60, 0, 0},   // Rotterdam (1)
      {0, 0, 0, 0, 40, 50, 0},  // Bordeaux (2)
      {0, 0, 0, 0, 0, 30, 0},   // Lisbon (3)
      {0, 0, 0, 0, 0, 0, 80},   // New York (4)
      {0, 0, 0, 0, 0, 0, 70},   // New Orleans (5)
      {0, 0, 0, 0, 0, 0, 0}     // Los Angeles (6)
  };

  int s = 0; // Noeud de départ
  int t = 5; // Noeud d'arrivée

  // Vecteur pour sauvegarder les prédécesseurs des sommets sur le chemin améliorant
  // On initialise ce vecteur à la taille du graphe et on le remplie avec des -1
  vector<int> predDansCheminAmeliorant(grapheEtCapacites.size(), -1);

  // Appel de la fonction parcoursLargeur
  bool existeChemin = parcoursLargeur(grapheEtCapacites, s, t, predDansCheminAmeliorant);

  if (existeChemin)
  {
    // Reconstruction du chemin améliorant
    vector<int> cheminAmeliorant = reconstruireChemin(s, t, predDansCheminAmeliorant);

    // Affichage du chemin améliorant
    cout << "Chemin améliorant de " << s << " à " << t << " : ";
    for (int sommet : cheminAmeliorant)
    {
      cout << sommet << " ";
    }
    cout << endl;
  }
  else
  {
    cout << "Il n'existe pas de chemin reliant " << s << " à " << t << endl;
  }

  return 0;
}
