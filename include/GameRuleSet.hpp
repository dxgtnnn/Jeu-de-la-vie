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
        // Constructeur: initialise avec la règle spécifiée (par défaut CLASSIC)
        GameRuleSet(RuleType rule = RuleType::CLASSIC);

        // Applique la règle d'évolution actuellement active et retourne le nouvel état
        Cell* applyRule(Cell* current, int neighbors) const;

        // Change la règle d'évolution active
        void setRule(RuleType rule);

        // Retourne l'enum de la règle d'évolution actuellement active
        RuleType getRule() const;

        // Retourne le nom descriptif de la règle actuellement active (ex: "Classic (Conway)")
        string getRuleName() const;
};