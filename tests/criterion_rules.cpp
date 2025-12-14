#include <criterion/criterion.h>
#include "GameRuleSet.hpp"
#include "AliveCell.hpp"
#include "DeadCell.hpp"

Test(Rules, set_and_get_rule_name) {
    GameRuleSet rules;
    rules.setRule(RuleType::HIGHLIFE);
    cr_assert_eq(rules.getRule(), RuleType::HIGHLIFE);
    cr_assert(rules.getRuleName().find("HighLife") != std::string::npos, "Rule name should contain HighLife");
}
