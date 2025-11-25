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
        void initialize(const string path);
        void update();
        void game(RenderWindow& window);
        int countNeighbors(int x, int y) const;
        void clickCell(int x, int y);
        void clear();
        void randomize();
        bool getCellState(int x, int y) const;
        string getState() const;
        int getWidth();
        int getHeight();
};
