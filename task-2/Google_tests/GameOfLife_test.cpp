#include "gtest/gtest.h"
#include "../src/GameEngine.h"

// Helper function to check if two grids are equal
bool gridsAreEqual(Grid grid1, Grid grid2) {
    if (grid1.getRow() != grid2.getRow() || grid1.getColumn() != grid2.getColumn()) {
        return false;
    }
    std::vector<std::vector<bool>> g1 = grid1.getGrid();
    std::vector<std::vector<bool>> g2 = grid2.getGrid();
    for (int i = 0; i < grid1.getRow(); ++i) {
        for (int j = 0; j < grid1.getColumn(); ++j) {
            if (g1[i][j] != g2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

TEST(GameEngineTest, EmptyGrid) {
Grid initialGrid(3, 3);
GameEngine engine(initialGrid, {3}, {2, 3});
Grid resultGrid = engine.computeIterations(1);
Grid expectedGrid(3, 3); // All false

ASSERT_TRUE(gridsAreEqual(resultGrid, expectedGrid));
}


TEST(GameEngineTest, GliderPattern) {
Grid initialGrid(5, 5);
initialGrid.setElement(1, 0, true);
initialGrid.setElement(2, 1, true);
initialGrid.setElement(0, 2, true);
initialGrid.setElement(1, 2, true);
initialGrid.setElement(2, 2, true);
GameEngine engine(initialGrid, {3}, {2, 3});

Grid resultGrid = engine.computeIterations(4);

Grid expectedGrid(5, 5);
expectedGrid.setElement(1, 2, true);
expectedGrid.setElement(2, 3, true);
expectedGrid.setElement(0, 4, true);
expectedGrid.setElement(1, 4, true);
expectedGrid.setElement(2, 4, true);


ASSERT_TRUE(gridsAreEqual(resultGrid, expectedGrid));
}


TEST(GameEngineTest, BlockPattern) {
Grid initialGrid(4, 4);
initialGrid.setElement(1, 1, true);
initialGrid.setElement(2, 1, true);
initialGrid.setElement(1, 2, true);
initialGrid.setElement(2, 2, true);
GameEngine engine(initialGrid, {3}, {2, 3});
Grid resultGrid = engine.computeIterations(10);
ASSERT_TRUE(gridsAreEqual(resultGrid, initialGrid));
}

TEST(GameEngineTest, BlinkPattern) {
Grid initialGrid(5, 5);
initialGrid.setElement(1, 2, true);
initialGrid.setElement(2, 2, true);
initialGrid.setElement(3, 2, true);

GameEngine engine(initialGrid, {3}, {2, 3});

Grid resultGrid = engine.computeIterations(2);
Grid expectedGrid(5, 5);
expectedGrid.setElement(2, 1, true);
expectedGrid.setElement(2, 2, true);
expectedGrid.setElement(2, 3, true);

ASSERT_TRUE(gridsAreEqual(resultGrid, expectedGrid));
}

TEST(GameEngineTest, CustomBirthAndSurvivalConditions) {
Grid initialGrid(3, 3);
initialGrid.setElement(0, 0, true);
initialGrid.setElement(1, 1, true);
initialGrid.setElement(2, 2, true);
GameEngine engine(initialGrid, {1, 2}, {1}); // Birth with 1 or 2 neighbors, survive with 1 neighbor

Grid resultGrid = engine.computeIterations(1);

Grid expectedGrid(3, 3);
expectedGrid.setElement(0, 1, true);
expectedGrid.setElement(1, 0, true);
expectedGrid.setElement(1, 1, true);
expectedGrid.setElement(1, 2, true);
expectedGrid.setElement(2, 1, true);

ASSERT_TRUE(gridsAreEqual(resultGrid, expectedGrid));
}

TEST(GameEngineTest, InitialGridCheck)
{
Grid initialGrid(3,3);
initialGrid.setElement(0,0,true);
GameEngine engine(initialGrid,{3},{2,3});
Grid resultGrid = engine.computeIterations(0);
ASSERT_TRUE(gridsAreEqual(resultGrid, initialGrid));
}