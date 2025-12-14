#include "ObstacleCell.hpp"

bool ObstacleCell::isAlive() const
{
    return true;
}

bool ObstacleCell::isObstacle() const
{
    return true;
}

Cell* ObstacleCell::nextState(int neighbors) const
{
    (void)neighbors;
    return const_cast<ObstacleCell*>(this);
}
