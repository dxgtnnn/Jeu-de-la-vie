#include <criterion/criterion.h>
#include "GameRuleSet.hpp"
#include "AliveCell.hpp"
#include "DeadCell.hpp"

Test(Rules, life_is_short_behavior) {
    GameRuleSet rules(RuleType::LIFE_IS_SHORT);

    AliveCell a;
    Cell *nextA = rules.applyRule(&a, 2);
    // in Life is Short any alive cell dies
    cr_assert(!nextA->isAlive(), "Alive cell should die under Life is Short");
    delete nextA;

    DeadCell d;
    Cell *nextD = rules.applyRule(&d, 2);
    // dead cell with 2 neighbors becomes alive in Life is Short
    cr_assert(nextD->isAlive(), "Dead cell with 2 neighbors should become alive under Life is Short");
    delete nextD;
}

Test(Rules, set_and_get_rule_name) {
    GameRuleSet rules;
    rules.setRule(RuleType::HIGHLIFE);
    cr_assert_eq(rules.getRule(), RuleType::HIGHLIFE);
    cr_assert(rules.getRuleName().find("HighLife") != std::string::npos, "Rule name should contain HighLife");
}
