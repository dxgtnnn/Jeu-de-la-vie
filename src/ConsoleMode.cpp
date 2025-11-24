#include "ConsoleMode.hpp"
#include "Grid.hpp"

void ConsoleMode::run()
{
    string path;
    int iterations = 0;

    cout << "Fichier d'entree : ";
    cin >> path;
    cout << "Nombre d'iterations : ";
    cin >> iterations;

    Grid grid(192, 108, 1);
    grid.initialize(path);

    string outDir = path + "_out";
    create_directory(outDir);

    for (int i = 0; i < iterations; i++) {
        ofstream out(outDir + "/iteration_" + to_string(i) + ".txt");
        out << "input/192108\n";
        for (int y = 0; y < 108; y++) {
            for (int x = 0; x < 192; x++) {
                out << (grid.getCellState(x, y) ? 1 : 0);
                if (x < 191)
                    out << " ";
            }
            out << "\n";
        }
        grid.update();
    }

    cout << "Terminé ! Fichiers générés dans : " << outDir << endl;
}
