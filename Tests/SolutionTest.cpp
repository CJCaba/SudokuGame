/**
 * @file SolutionTest.cpp
 * @author Daniel Flanagan
 *
 * Class to test Solution class
 */

#include "pch.h"

#include <fstream>
#include <streambuf>
#include <gtest/gtest.h>
#include <wx/filename.h>
#include <Solution.h>

using namespace std;

class SolutionTest : public ::testing::Test {
protected:
    // Used to create the temp file
    void SetUp() override {
        tempFile = std::make_unique<wxFile>();
        tempFilePath = wxFileName::CreateTempFileName(wxT(""), tempFile.get());

        // Game tag content from "level0.xml"
        wxString xmlContent = R"(<game col="6" row="3">3 2 4 8 7 6 0 1 5 7 5 6 2 0 1 4 8 3 0 8 1 4 3 5 7 6 2 6 4 8 0 2 7 3 5 1 2 7 5 3 1 8 6 0 4 1 3 0 6 5 4 8 2 7 5 6 7 1 4 0 2 3 8 8 1 2 7 6 3 5 4 0 4 0 3 5 8 2 1 7 6</game>)";
        tempFile->Write(xmlContent);
        tempFile->Close();
    }

    // Deletes the temp file
    void TearDown() override {
        wxRemoveFile(tempFilePath);
    }

    std::unique_ptr<wxFile> tempFile;
    wxString tempFilePath;
};

// Tests that LoadSolution function from Solution class loads correctly
TEST_F(SolutionTest, LoadSolutionTest) {
//    wxXmlDocument doc;
//    ASSERT_TRUE(doc.Load(tempFilePath));
//
//    Solution solutionInstance;
//    wxXmlNode* rootNode = doc.GetRoot();
//    if (rootNode->GetName() == wxT("game")) {
//        solutionInstance.LoadSolution(rootNode);
//    }
//
//    // Expected values in solution
//    std::vector<int> values = {
//        3, 2, 4, 8, 7, 6, 0, 1, 5, 7, 5, 6, 2, 0, 1, 4, 8, 3, 0,
//        8, 1, 4, 3, 5, 7, 6, 2, 6, 4, 8, 0, 2, 7, 3, 5, 1, 2, 7,
//        5, 3, 1, 8, 6, 0, 4, 1, 3, 0, 6, 5, 4, 8, 2, 7, 5, 6, 7,
//        1, 4, 0, 2, 3, 8, 8, 1, 2, 7, 6, 3, 5, 4, 0, 4, 0, 3, 5,
//        8, 2, 1, 7, 6
//    };
//
//    // Constructs the expected solution vector
//    std::vector<SolutionNumber> expectedSolution;
//    int col = wxAtoi(rootNode->GetAttribute("col"));
//    int row = wxAtoi(rootNode->GetAttribute("row"));
//
//    int currentCol = col;
//    int currentRow = row;
//
//    for(int i = 0; i < values.size(); i++) {
//        expectedSolution.push_back(SolutionNumber(values[i], currentCol, currentRow));
//        currentCol++;
//        if (currentCol == col + 9)
//        {
//            currentCol = col;
//            currentRow++;
//        }
//
//    }
//
//    // Compares loaded solution values against expected ones.
//    const auto& loadedSolution = solutionInstance.GetSolutionNumbers();
//    ASSERT_EQ(loadedSolution.size(), expectedSolution.size());
//
//    for (size_t i = 0; i < loadedSolution.size(); i++) {
//        ASSERT_EQ(expectedSolution[i].GetValue(), loadedSolution[i]->GetValue());
//        ASSERT_EQ(expectedSolution[i].GetRow(), loadedSolution[i]->GetRow());
//        ASSERT_EQ(expectedSolution[i].GetColumn(), loadedSolution[i]->GetColumn());
//    }
}

