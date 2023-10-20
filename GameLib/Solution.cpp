/**
 * @file Solution.cpp
 * @author Daniel Flanagan
 */

#include "pch.h"
#include "Solution.h"

using namespace std;


/**
 * Constructor
 * Constructs object from information within game tag of level xml file
 * @param node the node containing the game tag
 * @param filename
 */
Solution::Solution(wxXmlNode *node)
{
    node->GetAttribute(L"col").ToDouble(&mColumn);
    node->GetAttribute(L"row").ToDouble(&mRow);

    // Set values for first and last rows/columns of scoreboard
    double currentRow = mRow;
    double currentColumn = mColumn;
    double finalRow = currentRow + 9;
    double finalColumn = currentColumn + 9;

    // Loop through rows to set row value of solution numbers
    while(currentRow <= finalRow){
        // Loop through columns to set column value of solution numbers
        while(currentColumn <= finalColumn){

            currentColumn += 1;
        }
        currentRow += 1;
        currentColumn = mColumn;
    }




}