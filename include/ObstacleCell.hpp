#pragma once
#include "Cell.hpp"

class ObstacleCell : public Cell {
    public:
        bool isAlive() const override;
        Cell *nextState(int neighbors) const override;
};
