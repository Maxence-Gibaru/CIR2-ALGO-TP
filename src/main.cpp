#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "functions.hpp"

int main()
{

  // Partie 2 étape 1
  // Initialisation de la matrice d'adjacence grapheEtCapacites
  std::vector<std::vector<int>> grapheEtCapacites = {
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

  return 0;
}
