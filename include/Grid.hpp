#pragma once

#include "Cell.hpp"
#include "Background.hpp"
#include "GameRuleSet.hpp"

class Grid {
    private:
        int width;
        int height;
        int cellSize;
        vector<vector<Cell*>> cells;
        Background *background;
        GameRuleSet *ruleSet;

    public:
        Grid(int width, int height, int cellSize);
        ~Grid();
        void initialize(const string path);
        void update();
        void game(RenderWindow &window);
        int countNeighbors(int x, int y) const;
        bool getCellState(int x, int y) const;
        string getState() const;
        int getWidth();
        int getHeight();
        Cell *getCell(int x, int y);
        void setCell(int x, int y, Cell *newCell);
        void setBackground(const string &path, float opacity = 100.0f);
        void removeBackground();
        void updateBackgroundSize(int windowWidth, int windowHeight);
        void setRuleSet(RuleType rule);
        RuleType getCurrentRule() const;
        string getCurrentRuleName() const;
};