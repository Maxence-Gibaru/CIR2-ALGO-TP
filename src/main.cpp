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

  if (DISPLAY)
  {
    displayMadj(grapheEtCapacites);
  }

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

  if (DISPLAY)
  {
    for (int i = 0; i < predDansCheminAmeliorant.size(); i++)
    {
      std::cout << i << ":" << predDansCheminAmeliorant[i] << std::endl;
    }
  }

  if (DISPLAY)
  {
    if (existeChemin)
    {
      // Reconstruction du chemin améliorant
      std::vector<int> cheminAmeliorant = reconstruireChemin(s, t, predDansCheminAmeliorant);

      // Affichage du chemin améliorant

      std::cout << "Premier Chemin améliorant de " << s << " à " << t << " : ";

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
  }

  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */
  /*                             Partie 2 - Étape 3/4 : L’algorithme de Ford-Fulkerson                                */
  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

  // En exécutant l'algorithme de Ford-Fulkerson sur notre graphe donné dans l'énoncé, on retrouve bien le flot maximal de 150.
  if (DISPLAY)
  {
    std::cout << fordFulkerson(grapheEtCapacites, s, t) << std::endl;
  }

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

  if (DISPLAY)
  {
    std::cout << fordFulkerson(graphePartie1, s, t) << std::endl;
  }

  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */
  /*                             Partie 3 - Étape 1 : Production libre et satisfaction de la demande                  */
  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

  int demFrance = 19;
  int demBelgique = 7;
  int demSuisse = 5;

  grapheType grapheUsine = {
      {0, INT32_MAX, INT32_MAX, INT32_MAX, 0}, // sommet 1
      {0, 0, 0, 0, demFrance},                 // sommet 2
      {0, 0, 0, 0, demBelgique},               // sommet 3
      {0, 0, 0, 0, demSuisse},                 // sommet 4
      {0, 0, 0, 0, 0},                         // sommet 5
  };

  s = 0; // Noeud de départ
  t = 4; // Noeud d'arrivée

  int flotMax = fordFulkerson(grapheUsine, s, t);

  if (DISPLAY)
  {
    std::cout << "Le flot maximal pour ce premier graphe est : " << flotMax << std::endl;
  }

  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */
  /*                             Partie 3 - Étape 2 : Production limitée et satisfaction de la demande                */
  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

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

  flotMax = fordFulkerson(grapheUsine, s, t);

  if (DISPLAY)
  {
    std::cout << "Le flot maximal pour ce deuxième graphe est : " << flotMax << std::endl;
  }

  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */
  /*                             Partie 3 - Étape 3 : Production et transfert limités                                 */
  /*                                          et satisfaction de la demande                                           */
  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

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

  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */
  /*                             Partie 3 - Étape 4 :  Production, transfert et stockage limités et                   */
  /*                                              satisfaction de la demande                                          */
  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

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

  if (DISPLAY)
  {
    std::cout << "Le flot maximal pour ce quatrième graphe est : " << flotMax << std::endl;
  }

  // faire le graphe à la main pour vérifier le résultat

  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */
  /*                                    Partie 3 - Étape 5 :  Demande aléatoire                                       */
  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

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

  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */
  /*                                       Partie 4 : Prise en compte des coûts                                       */
  /*-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

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
    for (int i = 0; i < grapheUsineCout.size(); i++)
    {
      for (int j = 0; j < grapheUsineCout.size(); j++)
      {

        std::cout << grapheUsineCout[i][j] << " | ";
      }
      std::cout << std::endl;
    }
  }

  /*fordFulkersonCost(grapheUsine, grapheUsineCout, s, t);*/

  grapheType grapheUsineCost = {
      {0, 12, 4, 7, 0},
      {0, 0, 6, 14, 0},
      {0, 18, 0, 21, 0},
      {0, 25, 9, 0, 0},
      {0, 0, 0, 0, 0},
  };

  demFrance = 15;
  capTransFB = 8;
  capTransBF = 8;
  capTransBS = 3;
  capTransSB = 3;
  capTransFS = 12;
  capTransSF = 12;

  grapheUsine = {
      {0, 64, 40, 28, 0},
      {0, 0, capTransFB, capTransFS, demFrance},
      {0, capTransBF, 0, capTransBS, demBelgique},
      {0, capTransSF, capTransSB, 0, demSuisse},
      {0, 0, 0, 0, 0},
  };

  if (DISPLAY)
  {
    std::cout << fordFulkerson(grapheUsine, 0, 4) << std::endl; // 27
  }
  fordFulkersonCost(grapheUsine, grapheUsineCost, 0, 4);

  std::cout << findMinCostForMaxFlow(grapheUsine, grapheUsineCost, 0, 4, 27) << std::endl;

  return 0;
}
