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
    void SetUp() override {
        tempFile = std::make_unique<wxFile>();
        tempFilePath = wxFileName::CreateTempFileName(wxT(""), tempFile.get());

        wxString xmlContent = R"(<game col="6" row="3">3 2 4 8 7 6 0 1 5 7 5 6 2 0 1 4 8 3 0 8 1 4 3 5 7 6 2 6 4 8 0 2 7 3 5 1 2 7 5 3 1 8 6 0 4 1 3 0 6 5 4 8 2 7 5 6 7 1 4 0 2 3 8 8 1 2 7 6 3 5 4 0 4 0 3 5 8 2 1 7 6</game>)";
        tempFile->Write(xmlContent);
        tempFile->Close();
    }

    void TearDown() override {
        wxRemoveFile(tempFilePath);
    }

    std::unique_ptr<wxFile> tempFile;
    wxString tempFilePath;
};

TEST_F(SolutionTest, LoadSolutionTest) {
    wxXmlDocument doc;
    ASSERT_TRUE(doc.Load(tempFilePath));

    Solution solutionInstance;
    wxXmlNode* rootNode = doc.GetRoot();
    if (rootNode->GetName() == wxT("game")) {
        solutionInstance.LoadSolution(rootNode);
    }

    int values[9][9] = {
        {3, 2, 4, 8, 7, 6, 0, 1, 5},
        {7, 5, 6, 2, 0, 1, 4, 8, 3},
        {0, 8, 1, 4, 3, 5, 7, 6, 2},
        {6, 4, 8, 0, 2, 7, 3, 5, 1},
        {2, 7, 5, 3, 1, 8, 6, 0, 4},
        {1, 3, 0, 6, 5, 4, 8, 2, 7},
        {5, 6, 7, 1, 4, 0, 2, 3, 8},
        {8, 1, 2, 7, 6, 3, 5, 4, 0},
        {4, 0, 3, 5, 8, 2, 1, 7, 6}
    };

    int (*loadedSolution)[9] = solutionInstance.GetSolutionNumbers();

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            ASSERT_EQ(values[i][j], loadedSolution[i][j]);
        }
    }
}


