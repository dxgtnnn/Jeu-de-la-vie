#include <criterion/criterion.h>
#include "AliveCell.hpp"
#include "DeadCell.hpp"
#include "ObstacleCell.hpp"

Test(CellsMore, setCell_replaces_previous) {
    // create a DeadCell pointer and then replace it
    DeadCell *d = new DeadCell();
    Cell *next = d->nextState(3);
    cr_assert(next->isAlive(), "DeadCell nextState(3) should produce an AliveCell");
    delete d;
    delete next;
}

Test(CellsMore, obstacle_isalive_and_nextstate_returns_self) {
    ObstacleCell o;
    cr_assert(o.isAlive(), "ObstacleCell::isAlive should return true");
    Cell *n = o.nextState(2);
    cr_assert(dynamic_cast<ObstacleCell*>(n) != nullptr, "ObstacleCell::nextState should return self (ObstacleCell)");
}
