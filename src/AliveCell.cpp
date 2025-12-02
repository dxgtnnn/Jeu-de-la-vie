#include "AliveCell.hpp"
#include "DeadCell.hpp"

// Retourne le nouvel état de cette cellule vivante basé sur le nombre de voisins
// Applique la règle de Conway: 2-3 voisins = survit, sinon = meurt
Cell* AliveCell::nextState(int neighbors) const
{
    if (neighbors == 2 || neighbors == 3)
        return new AliveCell();
    return new DeadCell();
}

// Indique que cette cellule est vivante
bool AliveCell::isAlive() const
{
    return true;
}