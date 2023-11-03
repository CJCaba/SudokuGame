/**
 * @file GameTest.cpp
 * @author Daniel Flanagan
 *
 * A test file for the Game class
 */

#include "pch.h"
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <gtest/gtest.h>
#include <wx/filename.h>
#include <Game.h>

using namespace std;

const wstring levelZero = L"LevelFiles/level0.xml";

class GameTest : public ::testing::Test {
protected:
    /**
    * Create a path to a place to put temporary files
    */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/game";
        if(!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;
    }

    /**
    * Read a file into a wstring and return it.
    * @param filename Name of the file to read
    * @return File contents
    */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                    istreambuf_iterator<char>());

        return str;
    }

    /**
    * Test to ensure new game file is correct
     */
    void TestNewGame(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

    }
};

/**
 * Test the constructor for Game class
 */
TEST_F(GameTest, Construct){
    Game game;
}

/**
 * File Traversal / Loading Test
 */
TEST_F(GameTest, Load){
    // Create a game
    Game game;

    game.Load(levelZero);

    // Successful item traversal if 81 items
    ASSERT_EQ(game.GetItems().size(), 81);
}