#pragma once

#include "Grid.hpp"

class GameRule {
    private:
        Grid* grid;

    public:
        GameRule(Grid* grid);
        ~GameRule() = default;
        void clear();
        void randomize();
        void invertAll();
        void clickCell(int x, int y);
        void explode(int x, int y, int radius);
        void spawnGlider(int startX, int startY);
        void spawnBlinker(int startX, int startY);
        void spawnToad(int startX, int startY);
        void spawnBeacon(int startX, int startY);
        void spawnPulsar(int startX, int startY);
        void spawnGliderGun(int startX, int startY);
        void spawnLightweightSpaceship(int startX, int startY);
        void spawnPentadecathlon(int startX, int startY);
        void spawnRandomPattern();
        void spawnSpaceshipGun(int startX, int startY);
        void setGrid(Grid* newGrid);
        void randomizeWithObstacles();
};