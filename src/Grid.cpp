#include "Grid.hpp"
#include "AliveCell.hpp"
#include "DeadCell.hpp"
#include "ObstacleCell.hpp"

Grid::Grid(int width, int height, int cellSize) : width(width), height(height), cellSize(cellSize), cells(width, vector<Cell*>(height, nullptr)) {}

Grid::~Grid()
{
    for (size_t i = 0; i < cells.size(); i++) {
        for (size_t j = 0; j < cells[i].size(); j++)
            delete cells[i][j];
    }
}

void Grid::initialize(const string path)
{
    ifstream file(path);
    int value = 0;

    if (!file) {
        cerr << "Erreur : impossible d'ouvrir le fichier " << path << "\n" << endl;
        exit(84);
    }
    file >> width >> height;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            file >> value;
            delete cells[x][y];
            if(value == 1)
                cells[x][y] = new AliveCell();
            else if (value == 0)
                cells[x][y] = new DeadCell();
            else
                cells[x][y] = new ObstacleCell();
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
            nx = (x + dx + width) % width;
            ny = (y + dy + height) % height;
            if (dynamic_cast<ObstacleCell*>(cells[nx][ny]))
                continue;
            if (cells[nx][ny]->isAlive())
                count++;
        }
    }

    return count;
}


void Grid::update()
{
    vector<vector<Cell*>> next(width, vector<Cell*>(height, nullptr));
    int neighbors = 0;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Cell* current = cells[x][y];

            if (dynamic_cast<ObstacleCell*>(current)) {
                next[x][y] = current;
            } else {
                neighbors = countNeighbors(x, y);
                next[x][y] = current->nextState(neighbors);
            }
        }
    }
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (!dynamic_cast<ObstacleCell*>(cells[x][y])) {
                delete cells[x][y];
            }
        }
    }
    cells.swap(next);
}


void Grid::game(RenderWindow& window)
{
    RectangleShape cellShape(Vector2f(cellSize - 1, cellSize - 1));

    window.clear();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            cellShape.setPosition(x * cellSize, y * cellSize);
            if (dynamic_cast<ObstacleCell*>(cells[x][y])) {
                cellShape.setFillColor(Color::Red);
                window.draw(cellShape);
            } else if (cells[x][y]->isAlive()) {
                cellShape.setFillColor(Color::White);
                window.draw(cellShape);
            } else {
                cellShape.setFillColor(Color(38, 196, 236, 150)); // Color(red, green, blue, opacity);
                window.draw(cellShape);
            }
        }
    }
    window.display();
}

void Grid::clickCell(int x, int y)
{
    x = (x + width) % width;
    y = (y + height) % height;
    Cell* old = cells[x][y];

    if (dynamic_cast<ObstacleCell*>(old))
        return;
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
    int r = 0;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if(!dynamic_cast<ObstacleCell*>(cells[x][y]))
                delete cells[x][y];
            r = rand() % 100;
            if(r < 33)
                cells[x][y] = new DeadCell();
            else if(r < 99)
                cells[x][y] = new AliveCell();
            else
                cells[x][y] = new ObstacleCell();
        }
    }
}



string Grid::getState() const
{
    ostringstream out;
    out << width << " " << height << "\n";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            out << (cells[x][y]->isAlive() ? 1 : 0);
            if (x < width - 1)
                out << " ";
        }
        out << "\n";
    }
    return out.str();
}

bool Grid::getCellState(int x, int y) const
{
    return cells[x][y]->isAlive();
}

void Grid::spawnGlider(int startX, int startY)
{
    int x = 0;
    int y = 0;

    vector<pair<int, int>> pattern = {
        {1, 0},
        {2, 1},
        {0, 2}, {1, 2}, {2, 2}
    };
    for (auto &p : pattern) {
        x = (startX + p.first + width) % width;
        y = (startY + p.second + height) % height;
        if (!dynamic_cast<ObstacleCell*>(cells[x][y])) {
            delete cells[x][y];
            cells[x][y] = new AliveCell();
        }
    }
}

int Grid::getHeight()
{
    return height;
}

int Grid::getWidth()
{
    return width;
}
