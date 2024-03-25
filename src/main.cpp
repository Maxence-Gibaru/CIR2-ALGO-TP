#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
#include "functions.hpp"
#include "config.hpp"

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

  grapheType grapheEtCapacites = {
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

  /*
  for (int i = 0; i < predDansCheminAmeliorant.size(); i++)
  {
    std::cout << i << ":" << predDansCheminAmeliorant[i] << std::endl;
  }
  */

  if (existeChemin)
  {
    // Reconstruction du chemin améliorant
    std::vector<int> cheminAmeliorant = reconstruireChemin(s, t, predDansCheminAmeliorant);

    // Affichage du chemin améliorant
    if (DISPLAY)
    {
      std::cout << "Premier Chemin améliorant de " << s << " à " << t << " : ";
    }
    for (int sommet : cheminAmeliorant)
    {
      std::cout << sommet << " ";
    }
    std::cout << std::endl;
  }
  else
  {
    if (DISPLAY)
    {
      std::cout << "Il n'existe pas de chemin reliant " << s << " à " << t << std::endl;
    }
  }

  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */
  /*                             Partie 2 - Étape 3/4 : L’algorithme de Ford-Fulkerson                                */
  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

  // En exécutant l'algorithme de Ford-Fulkerson sur notre graphe donné dans l'énoncé, on retrouve bien le flot maximal de 150.
  if (DISPLAY)
  {
    std::cout << fordFulkerson(grapheEtCapacites, s, t) << std::endl;
  }

  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */
  /*                             Partie 3 - Étape 1 : Production libre et satisfaction de la demande                  */
  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

  grapheType grapheUsine = {
      {0, INT32_MAX, INT32_MAX, INT32_MAX, 0},
      {0, 0, 0, 0, 19},
      {0, 0, 0, 0, 7},
      {0, 0, 0, 0, 5},
      {0, 0, 0, 0, 0},
  };

  s = 0; // Noeud de départ
  t = 4; // Noeud d'arrivée

  // Partie 3 etape 2

  grapheUsine = {
      {0, 25, 10, 8, 0},
      {0, 0, 0, 0, 19},
      {0, 0, 0, 0, 7},
      {0, 0, 0, 0, 5},
      {0, 0, 0, 0, 0},
  };

  // Partie 3 etape 3

  grapheUsine = {
      {0, 25, 10, 8, 0},
      {0, 0, 8, 12, 30},
      {0, 8, 0, 3, 7},
      {0, 3, 3, 0, 5},
      {0, 0, 0, 0, 0},
  };

  // Partie 3 etape 4

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

  // faire le graphe à la main pour vérifier le résultat

  int mySeed = 6 + 5 + 7 + 6 + 7;

  // Moteur de nombres aléatoires et distribution
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 25); // Pour des nombres entre 1 et 15, par exemple

  // len(Clement + Robin + Maxence + Mathis + Mohamad)

  std::srand(mySeed);

  demFrance1 = dis(gen);
  demFrance2 = dis(gen);
  demBelgique1 = dis(gen);
  demBelgique2 = dis(gen);
  demSuisse1 = dis(gen);
  demSuisse2 = dis(gen);

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

  for (int i = 0; i < 12; i++)
  {
    demFrance1 = dis(gen);
    demFrance2 = dis(gen);
    demBelgique1 = dis(gen);
    demBelgique2 = dis(gen);
    demSuisse1 = dis(gen);
    demSuisse2 = dis(gen);

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
  }

  return 0;
}
