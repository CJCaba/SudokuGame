/**
 * @file Solution.cpp
 * @author Daniel Flanagan
 */

#include "pch.h"
#include "Solution.h"
#include <wx/tokenzr.h>

using namespace std;


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

    int currentRow = startingRow;
    int currentCol = startingCol;

    for (auto& numStr : numbers)
    {
        int value;
        numStr.ToInt(&value); // Convert the string to an integer

        // Create a SolutionNumber and add it to mSolutionNumbers
        mSolutionNumbers.push_back(std::make_shared<SolutionNumber>(value, currentCol, currentRow));

        currentCol++;
        if (currentCol == startingCol + 9)
        {
            currentCol = startingCol;
            currentRow++;
        }
    }
}