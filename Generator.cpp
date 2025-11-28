#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));
    int width = 0;
    int height = 0;
    int value = 0;

    cout << "Largeur de la grille : ";
    cin >> width;
    cout << "Hauteur de la grille : ";
    cin >> height;
    string filename = "input/" + to_string(width) + "x" + to_string(height) + ".txt";
    ofstream file(filename);
    if (!file) {
        cerr << "Erreur : impossible de créer le fichier " << filename << endl;
        return 84;
    }
    file << width << " " << height << "\n";
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            value = rand() % 2;
            if (x > 0)
                file << " ";
            file << value;
        }
        file << "\n";
    }
    file.close();
    cout << "Fichier créé : " << filename << endl;
    return 0;
}