#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "functions.hpp"

int main()
{
  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */
  /*                             Partie 1 : Trace de l’algorithme de Ford-Fulkerson                                   */
  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

  /*
    voir README.md
  */

  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */
  /*                             Partie 2 - Étape 1 : Représentation mémoire du graphe                                */
  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

  // Initialisation de la matrice d'adjacence grapheEtCapacites
  // On fait le choix d'utiliser un type double vector afin d'utiliser les fonctions associées

  std::vector<std::vector<int>> grapheEtCapacites = {
      {0, 50, 70, 40, 0, 0, 0}, // Stuttgart (0)
      {0, 0, 0, 0, 60, 0, 0},   // Rotterdam (1)
      {0, 0, 0, 0, 40, 50, 0},  // Bordeaux (2)
      {0, 0, 0, 0, 0, 30, 0},   // Lisbon (3)
      {0, 0, 0, 0, 0, 0, 80},   // New York (4)
      {0, 0, 0, 0, 0, 0, 70},   // New Orleans (5)
      {0, 0, 0, 0, 0, 0, 0}     // Los Angeles (6)
  };

  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */
  /*                             Partie 2 - Étape 2 : Le parcours en largeur au service                               */
  /*                                       de la recherche du chemin améliorant                                       */
  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

  int s = 0; // Noeud de départ
  int t = 6; // Noeud d'arrivée

  // Vecteur pour sauvegarder les prédécesseurs des sommets sur le chemin améliorant
  // On initialise ce vecteur à la taille du graphe et on le remplie avec des -1
  std::vector<int> predDansCheminAmeliorant(grapheEtCapacites.size(), -1);

  // Appel de la fonction parcoursLargeur
  bool existeChemin = parcoursLargeur(grapheEtCapacites, s, t, predDansCheminAmeliorant);

  if (existeChemin)
  {
    // Reconstruction du chemin améliorant
    std::vector<int> cheminAmeliorant = reconstruireChemin(s, t, predDansCheminAmeliorant);

    // Affichage du chemin améliorant
    std::cout << "Chemin améliorant de " << s << " à " << t << " : ";
    for (int sommet : cheminAmeliorant)
    {
      std::cout << sommet << " ";
    }
    std::cout << std::endl;
  }
  else
  {
    std::cout << "Il n'existe pas de chemin reliant " << s << " à " << t << std::endl;
  }

  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */
  /*                             Partie 2 - Étape 3/4 : L’algorithme de Ford-Fulkerson                                */
  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

  // En exécutant l'algorithme de Ford-Fulkerson sur notre graphe donné dans l'énoncé, on retrouve bien le flot maximal de 150.
  std::cout << fordFulkerson(grapheEtCapacites, s, t) << std::endl;

  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */
  /*                             Partie 3 - Étape 1 : Production libre et satisfaction de la demande                  */
  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

  std::vector<std::vector<int>> grapheUsine = {
      {0, 25, 10, 8, 0},
      {0, 0, 0, 0, 19},
      {0, 0, 0, 0, 7},
      {0, 0, 0, 0, 5},
      {0, 0, 0, 0, 0},
  };

  s = 0; // Noeud de départ
  t = 4; // Noeud d'arrivée

  std::cout << fordFulkerson(grapheUsine, s, t) << std::endl;

  return 0;
}
