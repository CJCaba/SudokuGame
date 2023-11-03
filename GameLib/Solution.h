/**
 * @file Solution.h
 * @author Daniel Flanagan
 *
 * Class that holds the games solution
 */

#ifndef ARES_GAMELIB_SOLUTION_H
#define ARES_GAMELIB_SOLUTION_H

#include "Game.h"

/**
 * Implements a solution class
 */
class Solution
{
private:
    /// The game this solution is a part of
    Game *mGame;

    /// Point to store the starting row and column for the game's board
    wxPoint mPoint = wxPoint(0,0);

    /// A collection of Numbers that represents the game's solution
    int mSolutionNumbers[9][9]{};

public:
    Solution(Game *game);

    /// Default constructor (disabled)
    Solution() = delete;

    /// Copy constructor (disabled)
    Solution(const Solution &) = delete;

    /// Assignment operator
    void operator=(const Solution &) = delete;

    ~Solution();

    void LoadSolution(wxXmlNode *node);

    /**
     * Getter for mSolutionNumbers
     * @return array of numbers representing the solution
     */
    int (*GetSolutionNumbers())[9]
    {
        return mSolutionNumbers;
    }

    /**
     * The starting position for the board
     * @return
     */
    wxPoint GetBoardPosition()
    {
        return mPoint;
    }

    /**
     * Return a particular value from the solution
     * @param row The row the value appears in
     * @param col The column the value appears in
     * @return The value found at the given row and column
     */
    int GetValue(int row, int col){ return mSolutionNumbers[row][col]; }
};

#endif //ARES_GAMELIB_SOLUTION_H
