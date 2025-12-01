#include <criterion/criterion.h>
#include "GameRuleSet.hpp"
#include "AliveCell.hpp"
#include "DeadCell.hpp"

Test(RulesMore, highlife_birth_at_6) {
    GameRuleSet rules(RuleType::HIGHLIFE);
    DeadCell d;
    Cell *b6 = rules.applyRule(&d, 6);
    cr_assert(b6->isAlive(), "In HighLife a dead cell with 6 neighbors should be born");
    delete b6;
}

Test(RulesMore, seeds_rule_only_births_at_2) {
    GameRuleSet rules(RuleType::SEEDS);
    DeadCell d;
    Cell *b2 = rules.applyRule(&d, 2);
    cr_assert(b2->isAlive(), "In Seeds, dead with 2 neighbors becomes alive");
    delete b2;
    Cell *b3 = rules.applyRule(&d, 3);
    cr_assert(!b3->isAlive(), "In Seeds, dead with 3 neighbors should remain dead");
    delete b3;
}

Test(RulesMore, coral_growth_survival) {
    GameRuleSet rules(RuleType::CORAL_GROWTH);
    AliveCell a;
    // coral growth: alive survives with >=4 neighbors
    Cell *s4 = rules.applyRule(&a, 4);
    cr_assert(s4->isAlive(), "Coral Growth alive with 4 neighbors should survive");
    delete s4;
    Cell *s3 = rules.applyRule(&a, 3);
    cr_assert(!s3->isAlive(), "Coral Growth alive with 3 neighbors should die");
    delete s3;
}
