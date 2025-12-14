#pragma once

#include "Cell.hpp"

enum class RuleType {
    CLASSIC,
    LIFE_IS_SHORT,
    DAY_AND_NIGHT,
    MAZE,
    WRAPAROUND,
    LONELY_WORLD,
    SEEDS,
    HIGHLIFE,
    CORAL_GROWTH,
    STAFFORD
};

class GameRuleSet {
    private:
        RuleType currentRule;
        Cell *classicRule(Cell *current, int neighbors) const;
        Cell *lifeIsShortRule(Cell *current, int neighbors) const;
        Cell *dayAndNightRule(Cell *current, int neighbors) const;
        Cell *mazeRule(Cell *current, int neighbors) const;
        Cell *wrapAroundRule(Cell *current, int neighbors) const;
        Cell *lonelyWorldRule(Cell *current, int neighbors) const;
        Cell *seedsRule(Cell *current, int neighbors) const;
        Cell *highLifeRule(Cell *current, int neighbors) const;
        Cell *coralGrowthRule(Cell *current, int neighbors) const;
        Cell *staffordRule(Cell *current, int neighbors) const;

    public:

        GameRuleSet(RuleType rule = RuleType::CLASSIC);

        Cell* applyRule(Cell* current, int neighbors) const;

        void setRule(RuleType rule);

        RuleType getRule() const;

        string getRuleName() const;
};
