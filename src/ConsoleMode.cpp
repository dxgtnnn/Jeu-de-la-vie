#include "ConsoleMode.hpp"
#include "Grid.hpp"
#include <iostream>
#include <fstream>

void ConsoleMode::run() {
    string dim;
    int iterations;

    cout << "Dimensions ([Largeur]x[Hauteur]) : ";
    cin >> dim;
    cout << "Iterations : ";
    cin >> iterations;

    string path = "input/" + dim + ".txt";
    ifstream file(path);
    if (!file) {
        cerr << "Fichier introuvable !\n";
        return;
    }

    int w, h;
    file >> w >> h;
    file.close();

    Grid g(w, h, 1);
    g.initialize(path);

    string outDir = path + "_out";
    create_directory(outDir);

    for (int i = 0; i < iterations; i++) {
        ofstream out(outDir + "/iteration_" + to_string(i) + ".txt");
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++)
                out << g.getCellState(x, y) << (x < w - 1 ? ' ' : '\n');
        }
        g.update();
    }

    cout << "✓ Terminé → " << outDir << endl;
}
