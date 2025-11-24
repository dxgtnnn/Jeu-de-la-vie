#include "Grid.hpp"
#include "AliveCell.hpp"
#include "DeadCell.hpp"

Grid::Grid(int width, int height, int cellSize) : width(width), height(height), cellSize(cellSize), cells(width, vector<Cell*>(height, nullptr)) {}

Grid::~Grid() {
    for (auto& col : cells)
        for (Cell* c : col)
            delete c;
}

void Grid::initialize(const string path)
{
    ifstream file(path);
    int wid = 0;
    int hei = 0;
    int value = 0;

    if (!file) {
        cerr << "Erreur : impossible d'ouvrir le fichier " << path << "\n" << endl;
        exit(84);
    }
    file >> wid >> hei;
    if (wid != width || hei != height) {
        cerr << "Erreur : dimensions du fichier (" << wid << "x" << hei << ") différentes des dimensions de la grille (" << width << "x" << height << ")\n";
        exit(84);
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            file >> value;
            delete cells[x][y];
            if(value == 1)
                cells[x][y] = new AliveCell();
            else
                cells[x][y] = new DeadCell();
        }
    }
}

int Grid::countNeighbors(int x, int y) const
{
    int count = 0;
    int nx = 0;
    int ny = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0)
                continue;
            nx = x + dx;
            ny = y + dy;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                if (cells[nx][ny]->isAlive())
                    count++;
        }
    }
    return count;
}

void Grid::update()
{
    vector<vector<Cell*>> next(width, vector<Cell*>(height));
    int neighbors = 0;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            neighbors = countNeighbors(x, y);
            next[x][y] = cells[x][y]->nextState(neighbors);
        }
    }
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            delete cells[x][y];
    cells.swap(next);
}

void Grid::game(RenderWindow& window)
{
    RectangleShape cellShape(Vector2f(cellSize - 1, cellSize - 1));

    window.clear();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (cells[x][y]->isAlive()) {
                cellShape.setFillColor(Color::Blue);
                cellShape.setPosition(x * cellSize, y * cellSize);
                window.draw(cellShape);
            }
            if (!cells[x][y]->isAlive()) {
                cellShape.setFillColor(Color(255, 255, 255, 255)); // Color(red, green, blue, opacity);
                window.draw(cellShape);
            }
        }
    }
    window.display();
}

void Grid::clickCell(int x, int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;
    Cell *old = cells[x][y];
    if (old->isAlive())
        cells[x][y] = new DeadCell();
    else
        cells[x][y] = new AliveCell();
    delete old;
}

void Grid::clear()
{
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++) {
            delete cells[x][y];
            cells[x][y] = new DeadCell();
        }
}

void Grid::randomize()
{
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++) {
            delete cells[x][y];
            if (rand() % 2)
                cells[x][y] = new AliveCell();
            else
                cells[x][y] = new DeadCell();
        }
}