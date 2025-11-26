#include "GUI.hpp"

void GUI::run()
{
    const int cellSize = 10;
    int width = 0;
    int height = 0;
    int numgliders = 0;
    int x = 0;
    int y = 0;
    bool paused = false;
    string answer = "";
    string path = "";

    cout << "Dimensions ([Largeur]x[Hauteur]): ";
    cin >> answer;
    path = "input/" + answer + ".txt";
    ifstream file(path);
    file >> width >> height;
    file.close();
    RenderWindow window(VideoMode(width * cellSize, height * cellSize), "Game of Life");
    Grid grid(width, height, cellSize);
    grid.initialize(path);

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
                if (event.key.code == Keyboard::P) {
                    numgliders = 3 + rand() % 3;
                    for (int i = 0; i < numgliders; i++) {
                        int randomX = rand() % grid.getWidth();
                        int randomY = rand() % grid.getHeight();
                        grid.spawnGlider(randomX, randomY);
                    }
                }
            }
            if (event.type == Event::MouseButtonPressed) {
                x = event.mouseButton.x / cellSize;
                y = event.mouseButton.y / cellSize;
                if (event.mouseButton.button == Mouse::Left)
                    grid.clickCell(x, y);
                if (event.mouseButton.button == Mouse::Right)
                    grid.explode(x, y, 35);
            }
        }
        if (!paused)
            grid.update();
        window.clear();
        grid.game(window);
        sleep(milliseconds(50));
    }
}
