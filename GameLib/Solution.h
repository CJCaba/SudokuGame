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
    Game *mGame;

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
     * Determine whether a point on our virtual board is equal to the solution
     * @return bool of integer comparison
     */
    bool IsEqual(int num, int row, int col){ return mSolutionNumbers[row][col] == num; }

    /**
     * Return a particular value from the solution
     * @param row The row the value appears in
     * @param col The column the value appears in
     * @return The value found at the given row and column
     */
    int GetValue(int row, int col){ return mSolutionNumbers[row][col]; }
};

#endif //ARES_GAMELIB_SOLUTION_H
