/**
 * @file Solution.h
 * @author Daniel Flanagan
 *
 * Class that holds the games solution
 */

#ifndef ARES_GAMELIB_SOLUTION_H
#define ARES_GAMELIB_SOLUTION_H

/**
 * Implements a solution class
 */
class Solution
{
private:

    wxPoint mPoint;

    /// A collection of Numbers that represents the game's solution
    int mSolutionNumbers[9][9];

public:

    Solution();

    void LoadSolution(wxXmlNode *node);

    /**
     * Getter for mSolutionNumbers
     */
    int (*GetSolutionNumbers())[9]
    {
        return mSolutionNumbers;
    }


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
