#pragma once

#include "Grid.hpp"

class Game {
    public:
        // Constructeur par défaut
        Game() = default;
        
        // Lance la boucle principale: affiche un menu et exécute le mode choisi
        // (console ou GUI)
        void run();
};
