#include "DeadCell.hpp"
#include "AliveCell.hpp"

Cell* DeadCell::nextState(int neighbors) const
{
    if (neighbors == 3)
        return new AliveCell();
    return new DeadCell();
}

bool DeadCell::isAlive() const
{
    return false;
}
