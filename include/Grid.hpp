#pragma once

#include "Cell.hpp"
#include "Background.hpp"
#include "GameRuleSet.hpp"

class Grid {
    private:
        int width;
        int height;
        int cellSize;
        vector<vector<Cell*>> cells;
        Background *background;
        GameRuleSet *ruleSet;

    public:
        // Constructeur: initialise la grille avec les dimensions et la taille des cellules
        Grid(int width, int height, int cellSize);

        // Destructeur: libère toutes les cellules et ressources allouées dynamiquement
        ~Grid();

        // Charge la grille à partir d'un fichier (format: largeur hauteur, puis états cellules)
        void initialize(const string path);

        // Effectue une itération de simulation: chaque cellule passe à l'état suivant
        void update();

        // Affiche la grille à l'écran en utilisant SFML (rendu graphique)
        void game(RenderWindow &window);

        // Compte le nombre de voisins vivants autour d'une cellule (x, y)
        // Les obstacles ne sont pas comptabilisés
        int countNeighbors(int x, int y) const;

        // Retourne l'état vivant/mort de la cellule aux coordonnées (x, y)
        bool getCellState(int x, int y) const;

        // Retourne une chaîne représentant l'état actuel de la grille
        // Format: "largeur hauteur\nlignes d'états"
        string getState() const;

        // Retourne la largeur de la grille
        int getWidth();

        // Retourne la hauteur de la grille
        int getHeight();

        // Retourne un pointeur vers la cellule aux coordonnées (x, y)
        Cell *getCell(int x, int y);

        // Remplace la cellule aux coordonnées (x, y) par une nouvelle cellule
        // Supprime l'ancienne cellule s'il y en avait une
        void setCell(int x, int y, Cell *newCell);

        // Charge et définit un image de fond pour la grille
        // opacity est l'opacité du fond (0-100)
        void setBackground(const string &path, float opacity = 100.0f);

        // Supprime l'image de fond actuelle
        void removeBackground();

        // Ajuste la taille de l'image de fond aux dimensions de la fenêtre
        void updateBackgroundSize(int windowWidth, int windowHeight);

        // Recalcule la taille des cellules pour remplir la fenêtre
        // Adapte dynamiquement cellSize selon les dimensions de fenêtre
        void adaptCellSizeToWindow(int windowWidth, int windowHeight);

        // Change la règle d'évolution appliquée à chaque itération
        void setRuleSet(RuleType rule);

        // Retourne la règle d'évolution actuellement active
        RuleType getCurrentRule() const;

        // Retourne le nom de la règle d'évolution actuellement active
        string getCurrentRuleName() const;
};