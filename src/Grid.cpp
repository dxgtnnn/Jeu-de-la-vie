#include "Grid.hpp"
#include "AliveCell.hpp"
#include "DeadCell.hpp"
#include "ObstacleCell.hpp"
#include <set>

// Constructeur: initialise la grille vide avec toutes les cellules mortes
// et crée l'objet GameRuleSet par défaut
Grid::Grid(int width, int height, int cellSize) : width(width), height(height), cellSize(cellSize), background(nullptr), ruleSet(new GameRuleSet())
{
    cells = vector<vector<Cell*>>(width, vector<Cell*>(height, nullptr));
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            cells[x][y] = new DeadCell();
        }
    }
}

// Destructeur: libère toutes les cellules allouées, le fond et l'ensemble des règles
Grid::~Grid()
{
    for (size_t i = 0; i < cells.size(); i++) {
        for (size_t j = 0; j < cells[i].size(); j++)
            delete cells[i][j];
    }
    delete background;
    delete ruleSet;
}

// Charge l'état initial de la grille depuis un fichier
// Format du fichier: largeur hauteur suivi d'une grille de valeurs 0/1/2
void Grid::initialize(const string path)
{
    ifstream file(path);
    int value = 0;

    if (!file) {
        cerr << "Erreur : impossible d'ouvrir le fichier " << path << "\n" << endl;
        exit(84);
    }
    int newWidth = 0;
    int newHeight = 0;
    file >> newWidth >> newHeight;
    for (size_t i = 0; i < cells.size(); i++) {
        for (size_t j = 0; j < cells[i].size(); j++) {
            delete cells[i][j];
        }
    }
    width = newWidth;
    height = newHeight;
    cells = vector<vector<Cell*>>(width, vector<Cell*>(height, nullptr));
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            file >> value;
            if (value == 1)
                cells[x][y] = new AliveCell();
            else if (value == 0)
                cells[x][y] = new DeadCell();
            else
                cells[x][y] = new ObstacleCell();
        }
    }
}

// Compte le nombre de voisins vivants (non-obstacles) autour de la cellule (x, y)
// Les coordonnées enroulent à la bordure (grille toroïdale)
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
            if (cells[nx][ny]->isObstacle())
                continue;
            if (cells[nx][ny]->isAlive())
                count++;
        }
    }
    return count;
}

// Effectue une étape de simulation: calcule le nouvel état de chaque cellule
// Les obstacles restent inchangés; les autres cellules appliquent la règle active
void Grid::update()
{
    vector<vector<Cell*>> next(width, vector<Cell*>(height, nullptr));
    int neighbors = 0;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Cell* current = cells[x][y];
            if (current->isObstacle()) {
                // Les obstacles ne changent jamais - on les réutilise
                next[x][y] = current;
            } else {
                neighbors = countNeighbors(x, y);
                next[x][y] = ruleSet->applyRule(current, neighbors);
            }
        }
    }
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (!cells[x][y]->isObstacle()) {
                delete cells[x][y];
            }
        }
    }
    cells.swap(next);
}

// Affiche la grille à l'écran avec les couleurs appropriées:
// - Rouge pour les obstacles
// - Bleu semi-transparent pour les cellules vivantes
// - Blanc très transparent pour les cellules mortes
void Grid::game(RenderWindow &window)
{
    RectangleShape cellShape(Vector2f(cellSize - 1, cellSize - 1));

    window.clear();
    if (background && background->isLoaded()) {
        background->render(window);
    }
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            cellShape.setPosition(x * cellSize, y * cellSize);
            if (dynamic_cast<ObstacleCell*>(cells[x][y])) {
                cellShape.setFillColor(Color::Red);
                window.draw(cellShape);
            } else if (cells[x][y]->isAlive()) {
                cellShape.setFillColor(Color(0, 255, 255, 100));
                window.draw(cellShape);
            } else {
                cellShape.setFillColor(Color(0, 0, 0, 0));
                window.draw(cellShape);
            }
        }
    }
    window.display();
}

// Retourne une chaîne représentant l'état actuel de la grille
// Format: "largeur hauteur\n0 0 1 ...\n..." (0=mort, 1=vivant)
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

// Retourne true si la cellule aux coordonnées (x, y) est vivante, false sinon
bool Grid::getCellState(int x, int y) const
{
    return cells[x][y]->isAlive();
}

// Retourne la hauteur de la grille
int Grid::getHeight()
{
    return height;
}

// Retourne la largeur de la grille
int Grid::getWidth()
{
    return width;
}

// Retourne un pointeur vers la cellule aux coordonnées (x, y)
Cell* Grid::getCell(int x, int y)
{
    return cells[x][y];
}

// Remplace la cellule aux coordonnées (x, y) par une nouvelle cellule
// L'ancienne cellule est supprimée (free mémoire)
void Grid::setCell(int x, int y, Cell* newCell)
{
    delete cells[x][y];
    cells[x][y] = newCell;
}

// Charge une image de fond pour la grille avec l'opacité spécifiée
// Si le chargement échoue, le fond n'est pas appliqué
void Grid::setBackground(const string& path, float opacity)
{
    delete background;
    background = new Background(path, opacity);
    if (!background->load()) {
        delete background;
        background = nullptr;
    }
}

// Supprime l'image de fond actuelle s'il y en a une
void Grid::removeBackground()
{
    delete background;
    background = nullptr;
}

// Ajuste la taille de l'image de fond pour qu'elle correspond à la fenêtre
void Grid::updateBackgroundSize(int windowWidth, int windowHeight)
{
    if (background && background->isLoaded()) {
        background->fitToWindow(windowWidth, windowHeight);
    }
}

// Change la règle d'évolution (ex: CLASSIC, LIFE_IS_SHORT, etc.)
void Grid::setRuleSet(RuleType rule)
{
    ruleSet->setRule(rule);
}

// Retourne la règle d'évolution actuellement active
RuleType Grid::getCurrentRule() const
{
    return ruleSet->getRule();
}

// Retourne le nom (description) de la règle d'évolution actuellement active
string Grid::getCurrentRuleName() const
{
    if (ruleSet == nullptr)
        return "Unknown";
    return ruleSet->getRuleName();
}

// Recalcule la taille des cellules pour que la grille remplisse la fenêtre
// Adapte dynamiquement cellSize selon les dimensions de fenêtre fournies
void Grid::adaptCellSizeToWindow(int windowWidth, int windowHeight)
{
    int cellSizeByWidth = 0;
    int cellSizeByHeight = 0;

    cellSizeByWidth = windowWidth / width;
    cellSizeByHeight = windowHeight / height;
    cellSize = min(cellSizeByWidth, cellSizeByHeight);
    if (cellSize < 3)
        cellSize = 3;
    if (cellSize > 30)
        cellSize = 30;
}
