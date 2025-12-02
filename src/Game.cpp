#include "Game.hpp"
#include "ConsoleMode.hpp"
#include "GUI.hpp"

// Lance le jeu: affiche un menu pour choisir entre le mode console
// (enregistrement fichier) et le mode graphique (GUI)
void Game::run()
{
    int choice;
    ConsoleMode console;
    GUI gui;

    cout << "Choisissez un mode :" << endl;
    cout << "1 - Enregistrement dans des fichiers" << endl;
    cout << "2 - Visuel" << endl;
    cout << "Mon choix > ";
    cin >> choice;
    if (choice == 1)
        console.run();
    else if (choice == 2)
        gui.run();
    else
        cout << "Choix invalide." << endl;
}
