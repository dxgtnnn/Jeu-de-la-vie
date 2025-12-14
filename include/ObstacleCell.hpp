#pragma once
#include "Cell.hpp"

class ObstacleCell : public Cell {
    public:

        bool isAlive() const override;

        bool isObstacle() const override;

        Cell *nextState(int neighbors) const override;
};
