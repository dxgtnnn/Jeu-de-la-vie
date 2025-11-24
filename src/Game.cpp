#include "Game.hpp"
#include "ConsoleMode.hpp"
#include "GUI.hpp"

void Game::run()
{
    int choice;
    ConsoleMode console;
    GUI gui;

    cout << "Choisissez un mode :" << endl;
    cout << "1 - Mode console" << endl;
    cout << "2 - Mode graphique (SFML)" << endl;
    cout << "> ";
    cin >> choice;
    if (choice == 1)
        console.run();
    else if (choice == 2)
        gui.run();
    else
        cout << "Choix invalide." << endl;
}
