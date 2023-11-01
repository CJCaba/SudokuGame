/**
 * @file Solution.cpp
 * @author Daniel Flanagan
 */

#include "pch.h"
#include "Solution.h"
#include <wx/tokenzr.h>

using namespace std;

Solution::Solution()
{
    mPoint = wxPoint(0,0);
}

/**
 * Handles loading the game's solution
 * @param node
 * @return
 */
void Solution::LoadSolution(wxXmlNode* node)
{
    std::wstring gameContent = node->GetNodeContent().ToStdWstring();
    wxArrayString numbers = wxStringTokenize(gameContent, L" ");

    int startingCol, startingRow;
    node->GetAttribute(L"col").ToInt(&startingCol);
    node->GetAttribute(L"row").ToInt(&startingRow);
    mPoint.x = startingCol, mPoint.y = startingRow;

    int currentRow = 0;
    int currentCol = 0;

    for (auto& numStr : numbers)
    {
        int value;
        numStr.ToInt(&value);

        // Create a SolutionNumber and add it to mSolutionNumbers
        mSolutionNumbers[currentRow][currentCol] = value;

        currentCol++;
        if (currentCol >= 9)
        {
            currentCol = 0;
            currentRow++;
        }
    }
}


