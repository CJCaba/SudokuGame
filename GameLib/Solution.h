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

public:

    void LoadSolution(wxXmlNode* node);


};

#endif //ARES_GAMELIB_SOLUTION_H
