#include <criterion/criterion.h>
#include "Grid.hpp"
#include "AliveCell.hpp"
#include "DeadCell.hpp"

Test(Grid, cell_assignment) {
    Grid g(5, 5, 1);

    g.setCell(2, 2, new AliveCell());
    cr_assert(g.getCellState(2, 2) == true, "Cell should be alive after assignment");

    g.setCell(2, 2, new DeadCell());
    cr_assert(g.getCellState(2, 2) == false, "Cell should be dead after assignment");
}

Test(Grid, neighbor_count) {
    Grid g(3, 3, 1);

    g.setCell(1, 0, new AliveCell());
    g.setCell(1, 1, new AliveCell());
    g.setCell(1, 2, new AliveCell());

    cr_assert_eq(g.countNeighbors(1, 1), 2, "Center should have 2 neighbors");
    cr_assert_eq(g.countNeighbors(0, 1), 3, "Left cell should have 3 neighbors");
}

Test(Grid, dimensions) {
    Grid g(10, 7, 1);
    cr_assert_eq(g.getWidth(), 10);
    cr_assert_eq(g.getHeight(), 7);
}

Test(Grid, getState_format) {
    Grid g(2, 2, 1);
    // default grid is dead cells (0)
    std::string s = g.getState();
    // first line should contain width and height
    cr_assert(s.find("2 2") != std::string::npos, "State output should contain width and height");
}

Test(Grid, update_blinker_oscillator) {
    Grid g(5, 5, 1);
    // horizontal blinker centered at (2,2)
    g.setCell(1, 2, new AliveCell());
    g.setCell(2, 2, new AliveCell());
    g.setCell(3, 2, new AliveCell());

    g.update();

    // after one update it should be vertical at x=2, y=1..3
    cr_assert(g.getCellState(2, 1), "Blinker should have live cell at (2,1)");
    cr_assert(g.getCellState(2, 2), "Blinker should have live cell at (2,2)");
    cr_assert(g.getCellState(2, 3), "Blinker should have live cell at (2,3)");

    // ensure some previously alive cell turned dead (1,2 and 3,2 should be dead now)
    cr_assert(!g.getCellState(1, 2), "Blinker should have dead cell at (1,2) after update");
    cr_assert(!g.getCellState(3, 2), "Blinker should have dead cell at (3,2) after update");
}
