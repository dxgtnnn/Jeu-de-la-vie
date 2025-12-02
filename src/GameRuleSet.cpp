#include "GameRuleSet.hpp"
#include "AliveCell.hpp"
#include "DeadCell.hpp"
#include "ObstacleCell.hpp"

// Constructeur: initialise avec la règle spécifiée (par défaut CLASSIC)
GameRuleSet::GameRuleSet(RuleType rule) : currentRule(rule) {}

// Applique la règle d'évolution actuellement active en fonction du nombre de voisins
// Retourne un pointeur vers une nouvelle cellule représentant l'état suivant
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

// Change la règle d'évolution active
void GameRuleSet::setRule(RuleType rule)
{
    currentRule = rule;
}

// Retourne la règle d'évolution actuellement active
RuleType GameRuleSet::getRule() const
{
    return currentRule;
}

// Retourne le nom descriptif de la règle actuellement active
string GameRuleSet::getRuleName() const
{
    switch (currentRule) {
        case RuleType::CLASSIC:
            return "Classic (Conway)";
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

// Applique la règle classique de Conway:
// Vivante: 2-3 voisins = survit, sinon = meurt
// Morte: exactement 3 voisins = renaît, sinon = reste morte
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

// Applique la règle "Life is Short":
// Vivante: meurt toujours (la vie est courte!)
// Morte: 2 voisins = renaît, sinon = reste morte
Cell *GameRuleSet::lifeIsShortRule(Cell *current, int neighbors) const
{
    if (current->isAlive()) {
        return new DeadCell();
    } else {
        if (neighbors == 2)
            return new AliveCell();
        return new DeadCell();
    }
}

// Applique la règle "Day and Night":
// Vivante: 3,4,6,7,8 voisins = survit, sinon = meurt
// Morte: 3,6,7,8 voisins = renaît, sinon = reste morte
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

// Applique la règle "Maze":
// Vivante: 1-5 voisins = survit, sinon = meurt
// Morte: 3 voisins = renaît, sinon = reste morte
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

// Applique la règle "Wrap Around":
// Vivante: 2-4 voisins = survit, sinon = meurt
// Morte: 3-4 voisins = renaît, sinon = reste morte
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

// Applique la règle "Lonely World":
// Vivante: exactement 1 voisin = survit, sinon = meurt
// Morte: exactement 1 voisin = renaît, sinon = reste morte
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

// Applique la règle "Seeds":
// Vivante: meurt toujours
// Morte: exactement 2 voisins = renaît, sinon = reste morte
Cell *GameRuleSet::seedsRule(Cell *current, int neighbors) const
{
    if (!current->isAlive() && neighbors == 2)
        return new AliveCell();
    return new DeadCell();
}

// Applique la règle "HighLife":
// Vivante: 2-3 voisins = survit, sinon = meurt
// Morte: 3 ou 6 voisins = renaît, sinon = reste morte
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

// Applique la règle "Coral Growth":
// Vivante: 4-8 voisins = survit, sinon = meurt
// Morte: 3 voisins = renaît, sinon = reste morte
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

// Applique la règle "Stafford":
// Vivante: 3-5 voisins = survit, sinon = meurt
// Morte: 3, 6, 7 ou 8 voisins = renaît, sinon = reste morte
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
