#pragma once
#include "Cell.hpp"

class ObstacleCell : public Cell {
    public:
        // Retourne toujours true car un obstacle est considéré comme "vivant"
        // (mais immobile et indestructible)
        bool isAlive() const override;

        // Retourne true car il s'agit d'un obstacle
        bool isObstacle() const override;

        // Retourne 'this' (le pointeur vers cet objet) car un obstacle
        // ne change jamais d'état - il reste inchangé à chaque itération
        Cell *nextState(int neighbors) const override;
};
