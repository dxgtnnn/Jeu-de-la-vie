#pragma once
#include "Cell.hpp"

class ObstacleCell : public Cell {
    public:
        bool isAlive() const override;           // Retourne false (ou true selon choix visuel)
        Cell *nextState(int neighbors) const override; // Retourne toujours this type
};
