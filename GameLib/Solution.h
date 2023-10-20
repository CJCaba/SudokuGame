/**
 * @file Solution.h
 * @author Daniel Flanagan
 *
 * Class that holds the games solution
 */

#ifndef ARES_GAMELIB_SOLUTION_H
#define ARES_GAMELIB_SOLUTION_H

#include "SolutionNumber.h"

/**
 * Implements a solution class
 */
class Solution
{
private:

    /// A collection of Numbers that represents the game's solution
    std::vector<std::shared_ptr<SolutionNumber>> mSolutionNumbers;

    /// Column for top left cell of Sudoku grid
    double mColumn;

    /// Row for top left cell of Sudoku grid
    double mRow;

public:

    /// Copy constructor (disabled)
    Solution(const Solution &) = delete;

    void LoadSolution(wxXmlNode* node);


};

#endif //ARES_GAMELIB_SOLUTION_H
