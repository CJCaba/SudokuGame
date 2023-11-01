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
};

#endif //ARES_GAMELIB_SOLUTION_H
