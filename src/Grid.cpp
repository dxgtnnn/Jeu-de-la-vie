#include "Grid.hpp"
#include "AliveCell.hpp"
#include "DeadCell.hpp"
#include <cstdlib>
#include <ctime>

Grid::Grid(int width, int height, int cellSize) : width(width), height(height), cellSize(cellSize), cells(width, vector<Cell*>(height, nullptr)) {}

Grid::~Grid() {
    for (auto& col : cells)
        for (Cell* c : col)
            delete c;
}

void Grid::initialize()
{
    srand(time(0));
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (rand() % 2)
                cells[x][y] = new AliveCell();
            else
                cells[x][y] = new DeadCell();
        }
    }
}

int Grid::countNeighbors(int x, int y) const
{
    int count = 0;
    int nx;
    int ny;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
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

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int neighbors = countNeighbors(x, y);
            next[x][y] = cells[x][y]->nextState(neighbors);
        }
    }
    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
            delete cells[x][y];
    cells = next;
}

void Grid::render(RenderWindow& window)
{
    RectangleShape cellShape(Vector2f(cellSize - 1, cellSize - 1));
    cellShape.setFillColor(Color::White);

    window.clear();
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (cells[x][y]->isAlive()) {
                cellShape.setPosition(x * cellSize, y * cellSize);
                window.draw(cellShape);
            }
        }
    }
    window.display();
}
