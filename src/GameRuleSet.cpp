#include "GameRuleSet.hpp"
#include "AliveCell.hpp"
#include "DeadCell.hpp"
#include "ObstacleCell.hpp"

GameRuleSet::GameRuleSet(RuleType rule) : currentRule(rule) {}

Cell *GameRuleSet::applyRule(Cell *current, int neighbors) const
{
    switch (currentRule) {
        case RuleType::CLASSIC:
            return classicRule(current, neighbors);
        case RuleType::LIFE_IS_SHORT:
            return lifeIsShortRule(current, neighbors);
        case RuleType::DAY_AND_NIGHT:
            return dayAndNightRule(current, neighbors);
        case RuleType::MAZE:
            return mazeRule(current, neighbors);
        case RuleType::WRAPAROUND:
            return wrapAroundRule(current, neighbors);
        case RuleType::LONELY_WORLD:
            return lonelyWorldRule(current, neighbors);
        case RuleType::SEEDS:
            return seedsRule(current, neighbors);
        case RuleType::HIGHLIFE:
            return highLifeRule(current, neighbors);
        case RuleType::CORAL_GROWTH:
            return coralGrowthRule(current, neighbors);
        case RuleType::STAFFORD:
            return staffordRule(current, neighbors);
        default:
            return classicRule(current, neighbors);
    }
}

void GameRuleSet::setRule(RuleType rule)
{
    currentRule = rule;
}

RuleType GameRuleSet::getRule() const
{
    return currentRule;
}

string GameRuleSet::getRuleName() const
{
    switch (currentRule) {
        case RuleType::CLASSIC:
            return "Classic";
        case RuleType::LIFE_IS_SHORT:
            return "Life is Short";
        case RuleType::DAY_AND_NIGHT:
            return "Day and Night";
        case RuleType::MAZE:
            return "Maze";
        case RuleType::WRAPAROUND:
            return "Wrap Around";
        case RuleType::LONELY_WORLD:
            return "Lonely World";
        case RuleType::SEEDS:
            return "Seeds";
        case RuleType::HIGHLIFE:
            return "HighLife";
        case RuleType::CORAL_GROWTH:
            return "Coral Growth";
        case RuleType::STAFFORD:
            return "Stafford";
        default:
            return "Unknown";
    }
}

Cell *GameRuleSet::classicRule(Cell *current, int neighbors) const
{
    if (current->isAlive()) {
        if (neighbors == 2 || neighbors == 3)
            return new AliveCell();
        return new DeadCell();
    } else {
        if (neighbors == 3)
            return new AliveCell();
        return new DeadCell();
    }
}

Cell *GameRuleSet::lifeIsShortRule(Cell *current, int neighbors) const
{
    if (current->isAlive()) {
        if (neighbors == 2)
            return new AliveCell();
        return new DeadCell();
    } else {
        if (neighbors == 2)
            return new AliveCell();
        return new DeadCell();
    }
}

Cell *GameRuleSet::dayAndNightRule(Cell *current, int neighbors) const
{
    if (current->isAlive()) {
        if (neighbors == 3 || neighbors == 4 || neighbors == 6 || neighbors == 7 || neighbors == 8)
            return new AliveCell();
        return new DeadCell();
    } else {
        if (neighbors == 3 || neighbors == 6 || neighbors == 7 || neighbors == 8)
            return new AliveCell();
        return new DeadCell();
    }
}

Cell *GameRuleSet::mazeRule(Cell *current, int neighbors) const
{
    if (current->isAlive()) {
        if (neighbors >= 1 && neighbors <= 5)
            return new AliveCell();
        return new DeadCell();
    } else {
        if (neighbors == 3)
            return new AliveCell();
        return new DeadCell();
    }
}

Cell *GameRuleSet::wrapAroundRule(Cell *current, int neighbors) const
{
    if (current->isAlive()) {
        if (neighbors >= 2 && neighbors <= 4)
            return new AliveCell();
        return new DeadCell();
    } else {
        if (neighbors == 3 || neighbors == 4)
            return new AliveCell();
        return new DeadCell();
    }
}

Cell *GameRuleSet::lonelyWorldRule(Cell *current, int neighbors) const
{
    if (current->isAlive()) {
        if (neighbors == 1)
            return new AliveCell();
        return new DeadCell();
    } else {
        if (neighbors == 1)
            return new AliveCell();
        return new DeadCell();
    }
}

Cell *GameRuleSet::seedsRule(Cell *current, int neighbors) const
{
    if (!current->isAlive() && neighbors == 2)
        return new AliveCell();
    return new DeadCell();
}

Cell *GameRuleSet::highLifeRule(Cell *current, int neighbors) const
{
    if (current->isAlive()) {
        if (neighbors == 2 || neighbors == 3)
            return new AliveCell();
        return new DeadCell();
    } else {
        if (neighbors == 3 || neighbors == 6)
            return new AliveCell();
        return new DeadCell();
    }
}

Cell *GameRuleSet::coralGrowthRule(Cell *current, int neighbors) const
{
    if (current->isAlive()) {
        if (neighbors >= 4 && neighbors <= 8)
            return new AliveCell();
        return new DeadCell();
    } else {
        if (neighbors == 3)
            return new AliveCell();
        return new DeadCell();
    }
}

Cell *GameRuleSet::staffordRule(Cell *current, int neighbors) const
{
    if (current->isAlive()) {
        if (neighbors >= 3 && neighbors <= 5)
            return new AliveCell();
        return new DeadCell();
    } else {
        if (neighbors == 3 || neighbors == 6 || neighbors == 7 || neighbors == 8)
            return new AliveCell();
        return new DeadCell();
    }
}
