#include "ConsoleMode.hpp"
#include "Grid.hpp"

void ConsoleMode::run()
{
    string answer = "";
    string path = "";
    string outpath = "";
    int iterations = 0;
    int wid = 0;
    int hei = 0;
    cout << "Dimensions ([largeur]x[hauteur]): ";
    cin >> answer;
    cout << "Nombre d'iterations : ";
    cin >> iterations;
    path = "input/" + answer + ".txt";
    ifstream file(path);
    file >> wid >> hei;
    file.close();
    Grid grid(wid, hei, 1);
    grid.initialize(path);
    outpath = path + "_out";
    create_directory(outpath);

    for (int i = 0; i < iterations; i++) {
        ofstream out(outpath + "/iteration_" + to_string(i) + ".txt");
        for (int y = 0; y < hei; y++) {
            for (int x = 0; x < wid; x++) {
                out << (grid.getCellState(x, y) ? 1 : 0);
                if (x < wid - 1)
                    out << " ";
            }
            out << "\n";
        }
        grid.update();
    }
    cout << "Terminé ! Fichiers générés dans : " << outpath << endl;
}
