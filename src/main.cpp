#include "Game.hpp"

int main()
{
    const int cellSize = 10;
    const int gridWidth = 192;
    const int gridHeight = 108;

    Game game(gridWidth, gridHeight, cellSize, "input/192108.txt");
    game.run();

    return 0;
}
