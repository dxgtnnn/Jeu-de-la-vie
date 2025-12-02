#include "ObstacleCell.hpp"

// Retourne true car un obstacle est considéré comme "vivant"
bool ObstacleCell::isAlive() const
{
    return true;
}

// Indique que c'est un obstacle (cellule non remplaçable)
bool ObstacleCell::isObstacle() const
{
    return true;
}

// Retourne un pointeur sur cet objet (this) car les obstacles ne changent jamais
// Important: l'appelant NE DOIT PAS supprimer ce pointeur car il n'a pas été
// alloué dynamiquement ici - c'est un pointeur vers l'objet existant
Cell* ObstacleCell::nextState(int neighbors) const
{
    (void)neighbors;
    return const_cast<ObstacleCell*>(this);
}
