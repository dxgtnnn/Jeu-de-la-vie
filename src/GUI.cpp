#include "GUI.hpp"


void GUI::run()
{
    const int cellSize = 10;
    const int width = 192;
    const int height = 108;
    RenderWindow window(VideoMode(width * cellSize, height * cellSize), "Game of Life");
    Grid grid(width, height, cellSize);
    grid.initialize("input/192108.txt");
    bool paused = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape)
                    window.close();
                if (event.key.code == Keyboard::Space)
                    paused = !paused;
                if (event.key.code == Keyboard::R)
                    grid.randomize();
                if (event.key.code == Keyboard::C)
                    grid.clear();
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                int x = event.mouseButton.x / cellSize;
                int y = event.mouseButton.y / cellSize;
                grid.clickCell(x, y);
            }
        }
        if (!paused)
            grid.update();
        window.clear();
        grid.game(window);
        sleep(milliseconds(50));
    }
}
