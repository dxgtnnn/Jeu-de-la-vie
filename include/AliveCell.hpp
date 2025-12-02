#pragma once

#include "Cell.hpp"

class AliveCell : public Cell {
    public:
        // Retourne toujours true car une cellule vivante est vivante
        bool isAlive() const override;

        // Calcule l'état suivant selon la règle de Conway:
        // - Si 2 ou 3 voisins: reste vivante
        // - Sinon: meurt (retourne une DeadCell)
        Cell *nextState(int neighbors) const override;
};