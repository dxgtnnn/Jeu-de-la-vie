#include "Game.hpp"

Game::Game(int width, int height, int cellSize, const string& filePath) : window(VideoMode(width * cellSize, height * cellSize), "Game of Life"), grid(width, height, cellSize), paused(false), cellSize(cellSize)
{
    grid.initialize(filePath);
}

void Game::run()
{
    while (window.isOpen()) {
        processEvents();
        if (!paused)
            update();
        render();
        sleep(milliseconds(50));
    }
}

void Game::processEvents()
{
    Event event;
    int x = 0;
    int y = 0;

    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Escape)
                window.close();
            if (event.key.code == Keyboard::Space)
                paused = !paused;
            if (event.key.code == Keyboard::C)
                grid.clear();
            if (event.key.code == Keyboard::R)
                grid.randomize();
        }
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            x = event.mouseButton.x / cellSize;
            y = event.mouseButton.y / cellSize;
            grid.clickCell(x, y);
        }
    }
}

void Game::update()
{
    grid.update();
}

void Game::render()
{
    window.clear();
    grid.game(window);
}
