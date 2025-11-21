#pragma once

#include "Cell.hpp"

class Grid {
    private:
        int width;
        int height;
        int cellSize;
        vector<vector<Cell*>> cells;

    public:
        Grid(int width, int height, int cellSize);
        ~Grid();
        void initialize();
        void update();
        void render(RenderWindow& window);
        int countNeighbors(int x, int y) const;
};