#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
using namespace filesystem;

class Cell {
public:
    virtual ~Cell() = default;
    virtual bool isAlive() const = 0;
    virtual Cell* nextState(int neighborCount) const = 0;
};
