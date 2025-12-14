#include "AliveCell.hpp"
#include "DeadCell.hpp"

Cell* AliveCell::nextState(int neighbors) const
{
    if (neighbors == 2 || neighbors == 3)
        return new AliveCell();
    return new DeadCell();
}

bool AliveCell::isAlive() const
{
    return true;
}
