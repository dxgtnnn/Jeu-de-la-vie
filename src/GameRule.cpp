#include "GameRule.hpp"
#include "AliveCell.hpp"
#include "DeadCell.hpp"
#include "ObstacleCell.hpp"

GameRule::GameRule(Grid* grid) : grid(grid) {}

void GameRule::clear()
{
    for (int x = 0; x < grid->getWidth(); x++) {
        for (int y = 0; y < grid->getHeight(); y++) {
            grid->setCell(x, y, new DeadCell());
        }
    }
}

void GameRule::randomize()
{
    int r = 0;
    for (int x = 0; x < grid->getWidth(); x++) {
        for (int y = 0; y < grid->getHeight(); y++) {
            if (!dynamic_cast<ObstacleCell*>(grid->getCell(x, y))) {
                r = rand() % 100;
                if (r < 50)
                    grid->setCell(x, y, new DeadCell());
                else
                    grid->setCell(x, y, new AliveCell());
            }
        }
    }
}

void GameRule::invertAll()
{
    for (int x = 0; x < grid->getWidth(); x++) {
        for (int y = 0; y < grid->getHeight(); y++) {
            Cell* current = grid->getCell(x, y);
            if (dynamic_cast<ObstacleCell*>(current))
                continue;
            if (current->isAlive())
                grid->setCell(x, y, new DeadCell());
            else
                grid->setCell(x, y, new AliveCell());
        }
    }
}

void GameRule::clickCell(int x, int y)
{
    int width = grid->getWidth();
    int height = grid->getHeight();

    x = (x + width) % width;
    y = (y + height) % height;
    Cell* current = grid->getCell(x, y);
    if (dynamic_cast<ObstacleCell*>(current))
        return;
    if (current->isAlive())
        grid->setCell(x, y, new DeadCell());
    else
        grid->setCell(x, y, new AliveCell());
}

void GameRule::explode(int x, int y, int radius)
{
    int width = grid->getWidth();
    int height = grid->getHeight();
    int nx = 0;
    int ny = 0;

    for (int dx = -radius; dx <= radius; dx++) {
        for (int dy = -radius; dy <= radius; dy++) {
            if (dx*dx + dy*dy > radius*radius)
                continue;
            nx = (x + dx + width) % width;
            ny = (y + dy + height) % height;
            Cell* current = grid->getCell(nx, ny);
            if (dynamic_cast<ObstacleCell*>(current))
                continue;
            if (!current->isAlive() && rand() % 100 < 70) {
                grid->setCell(nx, ny, new AliveCell());
            }
        }
    }
}

void GameRule::spawnGlider(int startX, int startY)
{
    int width = grid->getWidth();
    int height = grid->getHeight();
    int x = 0;
    int y = 0;

    vector<pair<int, int>> pattern = {
        {1, 0},
        {2, 1},
        {0, 2}, {1, 2}, {2, 2}
    };
    for (auto &p : pattern) {
        x = (startX + p.first + width) % width;
        y = (startY + p.second + height) % height;
        Cell* current = grid->getCell(x, y);
        if (!dynamic_cast<ObstacleCell*>(current)) {
            grid->setCell(x, y, new AliveCell());
        }
    }
}

void GameRule::spawnBlinker(int startX, int startY)
{
    int width = grid->getWidth();
    int height = grid->getHeight();
    int x = 0;
    int y = 0;

    vector<pair<int, int>> pattern = {
        {0, 0}, {1, 0}, {2, 0}
    };
    for (auto &p : pattern) {
        x = (startX + p.first + width) % width;
        y = (startY + p.second + height) % height;
        Cell* current = grid->getCell(x, y);
        if (!dynamic_cast<ObstacleCell*>(current)) {
            grid->setCell(x, y, new AliveCell());
        }
    }
}

void GameRule::spawnToad(int startX, int startY)
{
    int width = grid->getWidth();
    int height = grid->getHeight();
    int x = 0;
    int y = 0;

    vector<pair<int, int>> pattern = {
        {1, 0}, {2, 0}, {3, 0},
        {0, 1}, {1, 1}, {2, 1}
    };
    for (auto &p : pattern) {
        x = (startX + p.first + width) % width;
        y = (startY + p.second + height) % height;
        Cell* current = grid->getCell(x, y);
        if (!dynamic_cast<ObstacleCell*>(current)) {
            grid->setCell(x, y, new AliveCell());
        }
    }
}

void GameRule::spawnBeacon(int startX, int startY)
{
    int width = grid->getWidth();
    int height = grid->getHeight();
    int x = 0;
    int y = 0;

    vector<pair<int, int>> pattern = {
        {0, 0}, {1, 0},
        {0, 1},
        {3, 2},
        {2, 3}, {3, 3}
    };
    for (auto &p : pattern) {
        x = (startX + p.first + width) % width;
        y = (startY + p.second + height) % height;
        Cell* current = grid->getCell(x, y);
        if (!dynamic_cast<ObstacleCell*>(current)) {
            grid->setCell(x, y, new AliveCell());
        }
    }
}

void GameRule::spawnPulsar(int startX, int startY)
{
    int width = grid->getWidth();
    int height = grid->getHeight();
    int x = 0;
    int y = 0;

    vector<pair<int, int>> pattern = {
        {2,0},{3,0},{4,0},{8,0},{9,0},{10,0},
        {0,2},{5,2},{7,2},{12,2},
        {0,3},{5,3},{7,3},{12,3},
        {0,4},{5,4},{7,4},{12,4},
        {2,5},{3,5},{4,5},{8,5},{9,5},{10,5},
        {2,7},{3,7},{4,7},{8,7},{9,7},{10,7},
        {0,8},{5,8},{7,8},{12,8},
        {0,9},{5,9},{7,9},{12,9},
        {0,10},{5,10},{7,10},{12,10},
        {2,12},{3,12},{4,12},{8,12},{9,12},{10,12}
    };
    for (auto &p : pattern) {
        x = (startX + p.first + width) % width;
        y = (startY + p.second + height) % height;
        Cell* current = grid->getCell(x, y);
        if (!dynamic_cast<ObstacleCell*>(current)) {
            grid->setCell(x, y, new AliveCell());
        }
    }
}

void GameRule::spawnGliderGun(int startX, int startY)
{
    int width = grid->getWidth();
    int height = grid->getHeight();
    int x = 0;
    int y = 0;

    vector<pair<int, int>> pattern = {
        {24,0},
        {22,1},{24,1},
        {12,2},{13,2},{20,2},{21,2},{34,2},{35,2},
        {11,3},{15,3},{20,3},{21,3},{34,3},{35,3},
        {0,4},{1,4},{10,4},{16,4},{20,4},{21,4},
        {0,5},{1,5},{10,5},{14,5},{16,5},{17,5},{22,5},{24,5},
        {10,6},{16,6},{24,6},
        {11,7},{15,7},
        {12,8},{13,8}
    };
    for (auto &p : pattern) {
        x = (startX + p.first + width) % width;
        y = (startY + p.second + height) % height;
        Cell* current = grid->getCell(x, y);
        if (!dynamic_cast<ObstacleCell*>(current)) {
            grid->setCell(x, y, new AliveCell());
        }
    }
}

void GameRule::spawnLightweightSpaceship(int startX, int startY)
{
    int width = grid->getWidth();
    int height = grid->getHeight();
    int x = 0;
    int y = 0;

    vector<pair<int, int>> pattern = {
        {1,0},{4,0},
        {0,1},
        {0,2},{4,2},
        {0,3},{1,3},{2,3},{3,3}
    };
    for (auto &p : pattern) {
        x = (startX + p.first + width) % width;
        y = (startY + p.second + height) % height;
        Cell* current = grid->getCell(x, y);
        if (!dynamic_cast<ObstacleCell*>(current)) {
            grid->setCell(x, y, new AliveCell());
        }
    }
}

void GameRule::spawnPentadecathlon(int startX, int startY)
{
    int width = grid->getWidth();
    int height = grid->getHeight();
    int x = 0;
    int y = 0;

    vector<pair<int, int>> pattern = {
        {1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},
        {0,1},{3,1},{4,1},{5,1},{6,1},{9,1},
        {1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},{8,2}
    };
    for (auto &p : pattern) {
        x = (startX + p.first + width) % width;
        y = (startY + p.second + height) % height;
        Cell* current = grid->getCell(x, y);
        if (!dynamic_cast<ObstacleCell*>(current)) {
            grid->setCell(x, y, new AliveCell());
        }
    }
}

void GameRule::spawnRandomPattern()
{
    int patternChoice = rand() % 8;
    int count = 2 + rand() % 4;
    int randomX = 0;
    int randomY = 0;

    for (int i = 0; i < count; i++) {
        randomX = rand() % grid->getWidth();
        randomY = rand() % grid->getHeight();
        switch (patternChoice) {
            case 0:
                spawnGlider(randomX, randomY);
                break;
            case 1:
                spawnBlinker(randomX, randomY);
                break;
            case 2:
                spawnToad(randomX, randomY);
                break;
            case 3:
                spawnBeacon(randomX, randomY);
                break;
            case 4:
                spawnLightweightSpaceship(randomX, randomY);
                break;
            case 5:
                spawnPulsar(randomX, randomY);
                break;
            case 6:
                spawnPentadecathlon(randomX, randomY);
                break;
            case 7:
                spawnSpaceshipGun(randomX, randomY);
                break;
        }
        patternChoice = rand() % 7;
    }
}

void GameRule::setGrid(Grid* newGrid)
{
    grid = newGrid;
}

void GameRule::randomizeWithObstacles()
{
    int r = 0;

    for (int x = 0; x < grid->getWidth(); x++) {
        for (int y = 0; y < grid->getHeight(); y++) {
            if (!dynamic_cast<ObstacleCell*>(grid->getCell(x, y))) {
                r = rand() % 100;
                if (r < 45)
                    grid->setCell(x, y, new DeadCell());
                else if (r < 99)
                    grid->setCell(x, y, new AliveCell());
                else
                    grid->setCell(x, y, new ObstacleCell());
            }
        }
    }
}

void GameRule::spawnSpaceshipGun(int startX, int startY)
{
    int width = grid->getWidth();
    int height = grid->getHeight();
    int x = 0;
    int y = 0;

    vector<pair<int, int>> pattern = {
        {0,24},{1,22},{1,24},{2,12},{2,13},{2,20},{2,21},{2,34},{2,35},
        {3,11},{3,15},{3,20},{3,21},{3,34},{3,35},
        {4,0},{4,1},{4,10},{4,16},{4,20},{4,21},
        {5,0},{5,1},{5,10},{5,14},{5,16},{5,17},{5,22},{5,24},
        {6,10},{6,16},{6,22},{6,24},
        {7,11},{7,15},
        {8,12},{8,13}
    };
    for (auto &p : pattern) {
        x = (startX + p.first + width) % width;
        y = (startY + p.second + height) % height;
        Cell* current = grid->getCell(x, y);
        if (!dynamic_cast<ObstacleCell*>(current)) {
            grid->setCell(x, y, new AliveCell());
        }
    }
}
