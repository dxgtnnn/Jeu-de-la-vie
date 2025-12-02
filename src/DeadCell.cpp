#include "DeadCell.hpp"
#include "AliveCell.hpp"

// Retourne le nouvel état de cette cellule morte basé sur le nombre de voisins
// Applique la règle de Conway: exactement 3 voisins = renaît, sinon = reste morte
Cell* DeadCell::nextState(int neighbors) const
{
    if (neighbors == 3)
        return new AliveCell();
    return new DeadCell();
}

// Indique que cette cellule est morte
bool DeadCell::isAlive() const
{
    return false;
}