#include "GUI.hpp"


void GUI::run()
{
    const int cellSize = 10;
    int width = 0;
    int height = 0;
    bool paused = false;
    string answer = "";
    string path = "";

    cout << "Dimensions ([largeur]x[hauteur]): ";
    cin >> answer;
    path = "input/" + answer + ".txt";
    RenderWindow window(VideoMode(1920, 1080), "Game of Life");
    ifstream file(path);
    file >> width >> height;
    file.close();
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
