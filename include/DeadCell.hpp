#pragma once

#include "Cell.hpp"

class DeadCell : public Cell {
    public:
        bool isAlive() const override;
        Cell *nextState(int neighbors) const override;
};