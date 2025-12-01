#include <criterion/criterion.h>
#include <fstream>
#include "Grid.hpp"
#include "AliveCell.hpp"
#include "DeadCell.hpp"
#include "ObstacleCell.hpp"

Test(GridMore, initialize_and_getState_roundtrip) {
    // create a temp state file
    ofstream file("tests/tmp_state.txt");
    file << "3 2\n"; // width height
    file << "1 0 1\n";
    file << "0 1 0\n";
    file.close();

    Grid g(1,1,1);
    g.initialize("tests/tmp_state.txt");
    string s = g.getState();
    cr_assert(s.find("3 2") != string::npos, "State should contain dimensions from file");
    // cleanup
    remove("tests/tmp_state.txt");
}

Test(GridMore, update_block_still_life) {
    Grid g(4,4,1);
    // block at (1,1),(1,2),(2,1),(2,2)
    g.setCell(1,1, new AliveCell());
    g.setCell(1,2, new AliveCell());
    g.setCell(2,1, new AliveCell());
    g.setCell(2,2, new AliveCell());

    string before = g.getState();
    g.update();
    string after = g.getState();
    cr_assert_eq(before, after, "Block still life should not change after update");
}

Test(GridMore, obstacle_ignored_in_neighbor_count_and_preserved_on_update) {
    Grid g(3,3,1);
    // place obstacle in center
    g.setCell(1,1, new ObstacleCell());
    // place alive cells around obstacle
    g.setCell(0,1, new AliveCell());
    g.setCell(2,1, new AliveCell());
    // neighbors for (1,0) should count 2 (left and right), not the obstacle
    int c = g.countNeighbors(1,0);
    cr_assert_eq(c, 2, "Obstacle should be ignored when counting neighbors");

    // update: obstacle cell should remain obstacle
    g.update();
    Cell* center = g.getCell(1,1);
    cr_assert(dynamic_cast<ObstacleCell*>(center) != nullptr, "Obstacle cell should be preserved after update");
}
