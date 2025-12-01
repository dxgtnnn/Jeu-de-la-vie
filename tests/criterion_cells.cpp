#include <criterion/criterion.h>
#include "AliveCell.hpp"
#include "DeadCell.hpp"

Test(Cells, AliveCell_isAlive) {
    AliveCell c;
    cr_assert(c.isAlive(), "AliveCell should be alive");
}

Test(Cells, DeadCell_isAlive) {
    DeadCell c;
    cr_assert(!c.isAlive(), "DeadCell should not be alive");
}

Test(Cells, AliveCell_nextState_rule) {
    AliveCell c;
    Cell *next = c.nextState(1);
    cr_assert(!next->isAlive(), "AliveCell with 1 neighbor should die");
    delete next;
}

Test(Cells, DeadCell_nextState_rule) {
    DeadCell c;
    Cell *next = c.nextState(3);
    cr_assert(next->isAlive(), "DeadCell with 3 neighbors should become alive");
    delete next;
}
