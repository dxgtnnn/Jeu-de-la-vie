#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Cell {
public:
    virtual ~Cell() = default;

    virtual bool isAlive() const = 0;
    virtual Cell* nextState(int neighborCount) const = 0;
};