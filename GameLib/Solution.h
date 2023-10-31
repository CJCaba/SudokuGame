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

    int mRow;
    int mCol;

    /// A collection of Numbers that represents the game's solution
    int mSolutionNumbers[9][9];

public:

    void LoadSolution(wxXmlNode *node);

    /**
     * Getter for mSolutionNumbers
     */
    int **getSolutionNumbers()
    {
        return reinterpret_cast<int **>(mSolutionNumbers);

    }
};

#endif //ARES_GAMELIB_SOLUTION_H
