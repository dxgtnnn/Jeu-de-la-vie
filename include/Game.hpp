#pragma once

#include "Grid.hpp"

class Game {
    private:
        RenderWindow window;
        Grid grid;
        bool paused;
        int cellSize;

    public:
        Game(int width, int height, int cellSize, const string& filePath);
        void run();
        void processEvents();
        void update();
        void render();
};
