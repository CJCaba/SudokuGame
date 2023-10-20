/**
 * @file Solution.h
 * @author Daniel Flanagan
 *
 * Class that holds the games solution
 */

#ifndef ARES_GAMELIB_SOLUTION_H
#define ARES_GAMELIB_SOLUTION_H

#include "Item.h"

/**
 * Implements a solution class
 */
class Solution
{
private:

    /// A collection of Items that represents the game's solution
    std::vector<std::shared_ptr<Item>> mSolutionItems;

    /// Column for top left cell of Sudoku grid
    double mColumn;

    /// Row for top left cell of Sudoku grid
    double mRow;

protected:
    Solution(wxXmlNode *node);

public:
    /// Default constructor (disabled)
    Solution() = delete;

    /// Copy constructor (disabled)
    Solution(const Solution &) = delete;

    void LoadSolution(wxXmlNode *node);
};

#endif //ARES_GAMELIB_SOLUTION_H
