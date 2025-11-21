#include "Grid.hpp"

int main() {
    const int cellSize = 10;
    const int gridWidth = 250;
    const int gridHeight = 250;

    RenderWindow window(
        VideoMode(gridWidth * cellSize, gridHeight * cellSize),
        "Game of life"
    );

    Grid grid(gridWidth, gridHeight, cellSize);
    grid.initialize();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        grid.update();
        grid.render(window);

        sleep(milliseconds(100));
    }
}
