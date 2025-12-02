#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;
using namespace filesystem;

class Cell {
public:
    // Destructeur virtuel: permet de détruire correctement un objet Cell*
    // pointant vers une sous-classe (AliveCell, DeadCell, ObstacleCell)
    virtual ~Cell() = default;

    // Retourne si cette cellule est vivante (true) ou morte (false)
    virtual bool isAlive() const = 0;

    // Calcule l'état suivant de la cellule en fonction du nombre de voisins
    // Retourne un pointeur vers une nouvelle cellule allouée dynamiquement
    // (exception: ObstacleCell retourne 'this' pour rester inchangée)
    virtual Cell *nextState(int neighborCount) const = 0;

    // Indique si cette cellule est un obstacle (non remplaçable)
    // Retourne false par défaut; ObstacleCell la redéfinit pour retourner true
    // Permet d'éviter les vérifications de type avec dynamic_cast
    virtual bool isObstacle() const { return false; }
};
