#pragma once

#include "Cell.hpp"

class DeadCell : public Cell {
    public:
        // Retourne toujours false car une cellule morte est morte
        bool isAlive() const override;

        // Calcule l'état suivant selon la règle de Conway:
        // - Si exactement 3 voisins: renaît (retourne une AliveCell)
        // - Sinon: reste morte (retourne une DeadCell)
        Cell *nextState(int neighbors) const override;
};