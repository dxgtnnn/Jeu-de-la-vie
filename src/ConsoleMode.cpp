#include "ConsoleMode.hpp"
#include "Grid.hpp"

static bool getUserInput(string &filename, int &iterations)
{
    cout << "Dimensions ([Largeur]x[Hauteur]) : ";
    cin >> filename;
    cout << "Nombre d'iterations : ";
    cin >> iterations;
    return true;
}

static bool loadGridInfo(const string &filename, int &width, int &height)
{
    string path = "input/" + filename + ".txt";
    ifstream file(path);
    if (!file) {
        cerr << "❌ Fichier introuvable : " << path << endl;
        return false;
    }
    file >> width >> height;
    file.close();
    return true;
}

static void saveIteration(const string &outDir, Grid &grid, int width, int height, int iteration)
{
    ofstream out(outDir + "/iteration_" + to_string(iteration) + ".txt");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            out << (grid.getCellState(x, y) ? 1 : 0);
            if (x < width - 1) 
                out << " ";
        }
        out << "\n";
    }
}

void ConsoleMode::run()
{
    string filename;
    string path;
    string outDir;
    int iterations;
    int width, height;
    if (!getUserInput(filename, iterations))
        return;
    if (!loadGridInfo(filename, width, height))
        return;
    path = "input/" + filename + ".txt";
    Grid grid(width, height, 1);
    grid.initialize(path);
    outDir = filename + ".txt_out";
    create_directory(outDir);

    for (int i = 0; i < iterations; i++) {
        saveIteration(outDir, grid, width, height, i);
        grid.update();
    }
    cout << "✓ Terminé → " << outDir << endl;
}
