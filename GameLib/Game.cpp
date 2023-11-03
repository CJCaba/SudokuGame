/**
 * @file Game.cpp
 * @author Daniel Flanagan, Tyler Przybylo, and Jason Lin
 */

#include "pch.h"
#include "Game.h"
#include "Clock.h"
#include "Sparty.h"
#include "XRay.h"
#include "GivenNumber.h"
#include "InteractNumber.h"
#include "Solution.h"
#include "Container.h"
#include "Background.h"
#include "ImFullErrorMessage.h"
#include "Spotlight.h"

#include "InteractiveItems.h"
#include "VisitorNumbers.h"
#include "XRayVisitor.h"
#include "ContainerVisitor.h"

#include <algorithm>

using namespace std;

/// Path to Background Image (Hard Coded)
std::wstring const backgroundFileName = L"images/background.png";

/// Level 1
std::wstring const level1 = L"LevelFiles/level1.xml";

/// Hard Coded Level 1 Attributes
double gameWidth = 0;
double gameHeight = 0;

/// Text displayed when the player wins the game
const wxString WinText("Level Complete!");

/// Text displayed when the player loses the game
const wxString LoseText("Incorrect!");

/// Green colour for popup messages
const wxColour GreenColour(77, 167, 57);

const int numberKeyOffset = 48;

/**
 * Constructor for the game object
 */
Game::Game()
{
    mBackgroundImage = std::make_shared<wxImage>(backgroundFileName, wxBITMAP_TYPE_ANY);
    mGameSolution = std::make_shared<Solution>(this);
    mClock = std::make_shared<Clock>(this);
    mClock->Reset();
    mCurrentLevel = 1;
}

/**
 * Add an item to the game
 * @param item New item to add
 */
void Game::AddItem(std::shared_ptr<Item> item)
{
    // Code for setting an items location can go here

    mItems.push_back(item);
}

/**
 * Draw the game
 * @param graphics Graphics device to draw on
 * @param width Width of the window
 * @param height Height of the window
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, double width, double height)
{
    // Determine the size of the playing area in pixels
    // This is up to you...
    mPixelWidth = gameWidth * mTileWidth;
    mPixelHeight = gameHeight * mTileHeight;

    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(mPixelWidth);
    auto scaleY = double(height) / double(mPixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - mPixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > mPixelHeight * mScale)
    {
        mYOffset = (double)((height - mPixelHeight * mScale) / 2.0);
    }

    graphics->PushState();
    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    //
    // Draw in virtual pixels on the graphics context
    //
    // INSERT YOUR DRAWING CODE HERE

    //
    // Take Background Bitmap and Load Width & Height
    //
    if (mBackgroundBitmap.IsNull())
    {
        mBackgroundBitmap = graphics->CreateBitmapFromImage(*mBackgroundImage);
    }
    int backgroundWidth = mBackgroundImage->GetWidth();
    int backgroundHeight = mBackgroundImage->GetHeight();

    //
    // Draws Background
    //
    graphics->DrawBitmap(mBackgroundBitmap,
                         0, 0,
                         backgroundWidth,
                         backgroundHeight);

    // Drawing the Spotlight
    if (mSpotlight != nullptr)
    {
        mSpotlight->SetLocation((mSpotlightLocation.x - (mSpotlight->GetWidth() / 2)),
                                (mSpotlightLocation.y - (mSpotlight->GetHeight() / 2)));
    }

    // loop through items
    // if item is not in any containers
    // draw item
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }

    for (auto errorMessage : mErrorMessages)
    {
        errorMessage->Draw(graphics);
    }


    //
    // Checks if level is booting up
    //
    if(mStartUp && !mLevelWon && !mLevelLost)
    {
        //
        // Draws brief tutorial screen
        //

        // Draw tutorial box
        TutorialPrompt(graphics);

        if (mItems.empty())
            Load(level1);

        // After 3 seconds, remove tutorial and start game
        if(mClock->GetSeconds() == "03")
        {
            mStartUp = false;
            mClock->Reset();
        }
    }
    else
    {
        // Drawing Clock on Screen, should be Top Layer Drawing
        if(!mLevelWon)
        {
            mClock->Draw(graphics);
        }
    }

    if(mLevelWon || mLevelLost)
    {
        mStartUp = true;
        DrawEndScreen(graphics, mLevelWon ? WinText : LoseText);
        if(mFinishTime == -1)
        {
            mFinishTime = stoi(mClock->GetSeconds());
            mFinishTime += 3;
        }
        int currTime = stoi(mClock->GetSeconds());
        if(currTime == mFinishTime)
        {
            mFinishTime = -1;
            mLevelLost = false;
            if(mCurrentLevel == 1)
            {
                if(mLevelWon)
                {
                    SetLevel(L"LevelFiles/level2.xml");
                    mCurrentLevel = 2;
                }
                else {SetLevel(L"LevelFiles/level1.xml");}
            }

            else if (mCurrentLevel == 2)
            {
                if(mLevelWon)
                {
                    SetLevel(L"LevelFiles/level3.xml");
                    mCurrentLevel = 3;
                }
                else {SetLevel(L"LevelFiles/level2.xml");}
            }

            else {SetLevel(L"LevelFiles/level3.xml");}
        }
    }

    graphics->PopState();
}

/**
 * Updates and refreshes Game
 * @param elapsed Time passed since last refresh
 */
void Game::OnUpdate(double elapsed)
{
    if (mClock != nullptr)
    {
        mClock->AddTime(elapsed);
    }
    if (mSparty != nullptr)
    {
        mSparty->Update(elapsed);
    }

    for (auto it = mErrorMessages.begin(); it != mErrorMessages.end(); )
    {
        auto errorMessage = *it;
        errorMessage->Update(elapsed);

        if (errorMessage->ShouldBeDeleted())
        {
            it = mErrorMessages.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Implement Building the Virtual Solution Board
    if (!mStartUp){
        UpdateBoard();
        LevelSolutionCorrect();
    }
}

void Game::OnMouseMove(wxMouseEvent &event)
{
    double virtualX = ( event.GetX() - mXOffset ) / mScale;
    double virtualY = ( event.GetY() - mYOffset ) / mScale;

    if (WithinWidth(virtualX) && WithinHeight(virtualY))
    {
        mSpotlightLocation.x = virtualX;
        mSpotlightLocation.y = virtualY;
    }

}

void Game::OnLeftDown(wxMouseEvent &event)
{
    // First 3 seconds of the game, don't do anything
    if(mStartUp || mLevelWon)
        return;

    double virtualX = ( event.GetX() - mXOffset ) / mScale;
    double virtualY = ( event.GetY() - mYOffset ) / mScale;

    if (mSparty && WithinWidth(virtualX) && WithinHeight(virtualY))
        mSparty->MoveToPoint( wxPoint(virtualX, virtualY) );
}

/**
 * Save the game as a .game XML file.
 *
 * Open an XML file and stream the game data to it.
 *
 * @param filename The filename of the file to save the game to
 */
void Game::Save(const wxString &filename)
{

}

/**
 * Load the game from a .game XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the game from.
 */
void Game::Load(const wxString &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Game file");
        return;
    }

    Clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    root->GetAttribute("tilewidth", "1").ToInt(&mTileWidth);
    root->GetAttribute("tileheight", "1").ToInt(&mTileHeight);
    root->GetAttribute("width", "1").ToDouble(&gameWidth);
    root->GetAttribute("height", "1").ToDouble(&gameHeight);

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"declarations")
        {
            auto decChild = child->GetChildren();
            for ( ; decChild; decChild = decChild->GetNext())
            {
                XmlDeclare(decChild);
            }
        }
        else if (name == L"items")
        {
            auto decChild = child->GetChildren();
            for ( ; decChild; decChild = decChild->GetNext())
            {
                XmlItem(decChild);
            }
        }
        else if (name == L"game")
        {
            mGameSolution->LoadSolution(child);
        }
    }

    // Restart boot up sequence, makes the game load for 3 seconds
    mStartUp = true;
}

/**
 * Clear the Game data.
 *
 * Deletes all known items in the Game.
 */
void Game::Clear()
{
    mDeclarations.clear();
    mItems.clear();
    mBackgroundImage->Clear();
    mBackgroundBitmap.UnRef();
    mLevelWon = false;
    mLevelLost = false;
}

/**
 * Load a Declaration node into our map to store its information
 * Also load the given base image file into a wxImage and add to
 * a separate map
 * @param node The Declaration node to store
 */
void Game::XmlDeclare(wxXmlNode *node){
    string id = node->GetAttribute(L"id", L'0').ToStdString();
    auto name = node->GetName();
    wstring filename;
    if (name == "sparty")
    {
        filename = L"images/" + node->GetAttribute("image1", "").ToStdWstring();
    }
    else
    {
        filename = L"images/" + node->GetAttribute("image", "").ToStdWstring();
    }

    mDeclarations[id] = node;
    mImages[id] = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
}

/**
 * Load an Item derived from our declarations and add it to our game
 * @param node The Item node containing the position information and ID
 */
void Game::XmlItem(wxXmlNode *node){
    shared_ptr<Item> item;
    auto name = node->GetName();
    auto itemID = node->GetAttribute("id", "").ToStdString();
    auto itemDeclaration = mDeclarations[itemID];

    if(name == "given")
    {
        item = std::make_shared<GivenNumber>(this, itemDeclaration, node);

    }

    if(name == "digit")
    {
        item = std::make_shared<InteractNumber>(this, itemDeclaration, node);
    }

    if(name == "background")
    {
        item = std::make_shared<Background>(this, itemDeclaration, node);
    }

    if(name == "container")
    {
        item = std::make_shared<Container>(this, itemDeclaration, node);
    }

    if(name == "xray")
    {
        mXRay = std::make_shared<XRay>(this, itemDeclaration, node);
        item = mXRay;
    }

    if(name == "sparty")
    {
        mSparty = std::make_shared<Sparty>(this, itemDeclaration, node);
        item = mSparty;
    }

    if(name == "spotlight")
    {
        mSpotlight = std::make_shared<Spotlight>(this, itemDeclaration, node);
        item = mSpotlight;
    }

    if(item)
    {
        double x, y, height;

        node->GetAttribute("col", "0").ToDouble(&x);
        node->GetAttribute("row", "0").ToDouble(&y);
        itemDeclaration->GetAttribute("height", "0").ToDouble(&height);
        if (name == "background" || name == "container" || name == "xray"){
            item->SetLocation(x * mTileHeight, (y + 1) * mTileHeight - height);
        }
        else
        {
            item->SetLocation(x * mTileHeight, y * mTileHeight);
            if (name == "sparty")
            {
                mSparty->SetLocation(x * mTileWidth, y * mTileHeight);
                mSparty->MoveToPoint(wxPoint(x * mTileWidth, y * mTileHeight));
            }
        }

        AddItem(item);
    }
}

/**
 * Checks if current x value is outside of game range
 * @param x location in width
 * @return true if still within, else false
 */
bool Game::WithinWidth(double x)
{
    if (x > mPixelWidth || x < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * Checks if current y value is outside of game range
 * @param y location in height
 * @return true if still within, else false
 */
bool Game::WithinHeight(double y)
{
    if (y > mPixelHeight || y < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * Sets the level for loading
 * @param filename
 */
void Game::SetLevel(std::wstring filename)
{
    Clear();
    mStartUp = true;

    // Find the digit in the filename and convert it to an integer
    for (wchar_t wc : filename) {
        if (isdigit(wc)) {
            mCurrentLevel = wc - L'0';
            break;
        }
    }

    mClock->Reset();
    Load(filename);
}


/**
 * Handle the key down event
 * @param event The key event
 */
void Game::OnKeyDown(wxKeyEvent &event)
{
    if(mStartUp || mLevelWon)
        return;

    int keyCode = event.GetKeyCode();

    if (keyCode == WXK_SPACE)
    {
        mSparty->MakeEat();
        if (!mSparty->IsMoving())
        {
            auto target = mSparty->GetTargetPoint();
            double x = target.x;
            double y = target.y;

            // Visitor creating an array of interact numbers
            InteractiveItems visitorRed;
            Accept(&visitorRed);
            auto redNumbers = visitorRed.InteractFound();

            if (mXRay->IsFull())
                mErrorMessages.push_back(make_shared<ImFullErrorMessage>(wxPoint(GetWidth() / 2, GetHeight())));
            else
            {
                for(auto &item : redNumbers)
                {
                    // if item is found, add to xray and break
                    if(mXRay->Check(item))
                    {
                        continue;
                    }
                    if(item->HitTest(x, y))
                    {
                        mXRay->Add(item);
                        break;
                    }
                }
            }
        }
    }

        // Handler for 0 - 9 number keys
    else if (keyCode >= 48 && keyCode <= 57)
    {
        if (!mSparty->IsMoving())
        {
            auto target = mSparty->GetTargetPoint();
            int x = target.x;
            int y = target.y;

            auto dest = mGameSolution->GetBoardPosition();
            int col = dest.x * mTileWidth;
            int row = dest.y * mTileHeight;

            auto item = mXRay->Find(keyCode - numberKeyOffset);
            if (item != nullptr)
            {
                VisitorNumbers numVisitor;
                Accept(&numVisitor);
                auto numbers = numVisitor.FoundItems();

                for (auto num : numbers)
                {
                    if(num->HitTest(x,y))
                        return;
                }

                mSparty->MakeEat();

                if (x >= col && y >= row
                    && x <= col + (GetTileWidth() * 9)
                    && y <= row + (GetTileHeight() * 9))
                {
                    x /= GetTileWidth();
                    y /= GetTileHeight();

                    int newX = x;
                    int newY = y;

                    newX *= GetTileWidth();
                    newY *= GetTileHeight();

                    VisitorNumbers visitor;

                    item->SetLocation(newX,newY);
                }
                else
                {
                    item->SetLocation(x,y);
                }

                mXRay->Remove(item);
            }
        }
    }

    else if (keyCode == 66) // ASCII 66 = B
    {
        mSparty->MakeHeadButt();
        if (!mSparty->IsMoving())
        {
            auto target = mSparty->GetTargetPoint();
            double x = target.x;
            double y = target.y;

            // Visitor finding
            ContainerVisitor visitor;
            Accept(&visitor);

            auto container = visitor.ContainerFound();

            for (auto item : container) {
                if (item->HitTest(x, y))
                {
                    item->Release();
                }
            }
        }
    }
}

/**
 * Determines display text based on level
 * @param currentLevel level to display
 */
wstring Game::DetermineStartupText()
{
    if (mCurrentLevel == 1)
    {
        return L"Level 1 Begin";
    }
    else if (mCurrentLevel == 2)
    {
        return L"Level 2 Begin";
    }
    else if (mCurrentLevel == 3)
    {
        return L"Level 3 Begin";
    }
    else
    {
        // Default or error text in case mCurrentLevel has an unexpected value
        return L"Unknown Level";
    }
}

/**
 * Draw the Tutorial Prompt for our game
 * @param graphics The context to draw on
 */
void Game::TutorialPrompt(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(*wxBLACK);

    double rectWidth = mPixelWidth / 1.5;
    double rectHeight = mPixelHeight / 2.5;

    double rectX = (mPixelWidth / 2) - (rectWidth / 2);
    double rectY = (mPixelHeight / 2) - (rectHeight / 2);

    graphics->DrawRectangle(rectX, rectY,rectWidth, rectHeight);

    wxFont bigFont(wxSize(75, 75),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, GreenColour);

    // Determines which level to display in text box
    std::wstring displayText = DetermineStartupText();

    // Get text dimensions
    double titleWidth, titleHeight;
    graphics->GetTextExtent(displayText.c_str(), &titleWidth, &titleHeight);

    // Draw the determined text
    graphics->DrawText(displayText.c_str(),
                       rectX + (rectWidth/2) - (titleWidth/2),
                       rectY);

    // Draw guide for inputs
    double textWidth, textHeight;
    wxFont subFont(wxSize(50, 50),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(subFont, wxColour(0,0,0));

    graphics->GetTextExtent(L"Space = Eat", &textWidth, &textHeight);
    graphics->DrawText(L"Space = Eat",
                       rectX + (rectWidth/2) - (textWidth/2),
                       rectY + titleHeight);

    graphics->GetTextExtent(L"0-8 = Regurgitate", &textWidth, nullptr);
    graphics->DrawText(L"0-8 = Regurgitate",
                       rectX + (rectWidth/2) - (textWidth/2),
                       rectY + titleHeight + textHeight);

    graphics->GetTextExtent(L"B = Headbutt", &textWidth, nullptr);
    graphics->DrawText(L"B = Headbutt",
                       rectX + (rectWidth/2) - (textWidth/2),
                       rectY + titleHeight + (textHeight * 2));
}

/**
 * Draw the Tutorial Prompt for our game
 * @param graphics The context to draw on
 */
void Game::DrawEndScreen(std::shared_ptr<wxGraphicsContext> graphics, wxString EndText)
{
    // Rectangle properties
    wxPoint topLeft(0, 0);
    wxPoint bottomRight(GetWidth(), GetHeight());

    // Create a font and set it
    wxFont font(96, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxColour textColor(GreenColour);
    graphics->SetFont(font, textColor);

    // Calculate the text position to center it within the rectangle
    double textWidth, textHeight;
    graphics->GetTextExtent(EndText, &textWidth, &textHeight);
    wxPoint textPosition(topLeft.x + (bottomRight.x - textWidth) / 2, topLeft.y + (bottomRight.y - textHeight) / 2);

    // Draw the red text in the center of the rectangle
    graphics->DrawText(EndText, textPosition.x, textPosition.y);
}

/**
 * Getter to return a specific image file loaded from our Declarations
 * @param id The id attributed to a specific image
 * @return Pointer to wxImage
 */
std::shared_ptr<wxImage> Game::GetImage(const string& id){
    return mImages[id];
}

/**
 * Function to allow visitors to visit mItems
 * @param visitor The visitor that will visit each item
 */
void Game::Accept(Visitor *visitor)
{
    for (const auto &item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
 * Update our Virtual Game board with the current numbers placed on the sudoku
 */
void Game::UpdateBoard()
{
    // Obtain the starting point for the Sudoku Board
    auto point = mGameSolution->GetBoardPosition();

    // Obtain list of all current numbers on the board
    VisitorNumbers visNum;
    Accept(&visNum);
    auto numbers = visNum.FoundItems();

    int startCol = point.x;
    int endCol = point.x + 9;
    // Iterate through the Virtual Solution
    // and update the placement of numbers
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            // First set point to 9, a number not present in our game
            mSolution[row][col] = 9;
            for(auto item : numbers){
                // If a number is present on the point, add it to the board
                if (item->HitTest(point.x * mTileWidth, point.y * mTileHeight)){
                    mSolution[row][col] = item->GetValue();
                }
            }
            point.x++;
            if (point.x >= endCol){point.x = startCol;}
        }
        point.y++;
    }
}

/**
  * Compares the expected solution to the current solution.
  * If solution matches, mLevelWon set to True.
  */
void Game::LevelSolutionCorrect() {
    int (*expectedSolution)[9] = mGameSolution->GetSolutionNumbers();
    bool arraysAreIdentical = true;
    bool boardFull = true;
    for (int i = 0; i < 9 && arraysAreIdentical; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (expectedSolution[i][j] != mSolution[i][j])
            {
                arraysAreIdentical = false;
                if(mSolution[i][j] == 9) {boardFull = false;}
                break;
            }
        }
    }
    if (arraysAreIdentical)
    {
        mLevelWon = true;
    }
    if(boardFull && !arraysAreIdentical)
    {
        mLevelLost = true;
    }
}

/**
 * Solve the board with current interactive numbers in mItems
 */
void Game::Solve() {
    // Obtain the starting point for the Sudoku Board
    auto point = mGameSolution->GetBoardPosition();

    // Collect all current interactive numbers in mItems
    InteractiveItems visitor;
    Accept(&visitor);

    auto numbers = visitor.InteractFound();

    // Move all Interactable Numbers off of the virtual board
    for(auto item : numbers){
        if(mXRay->Check(item))
        {
            continue;
        }
        item->SetLocation(0,0);
    }

    UpdateBoard();

    int startCol = point.x;
    int endCol = point.x + 9;
    // Iterate through the virtual board to see if we need to place a number there.
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            int boardValue = mSolution[row][col];
            int solValue = mGameSolution->GetValue(row, col);
            // If they are not equal, find a number that can be placed there
            if(!mGameSolution->IsEqual(boardValue, row, col)){
                for(auto item : numbers){
                    if(item->GetValue() == solValue){
                        // Ensure the current item isn't already placed on the board
                        if(!item->OnBoard(mGameSolution->GetBoardPosition()))
                        {
                            if(mXRay->Check(item))
                            {
                                continue;
                            }
                            item->SetLocation(point.x * 48, point.y * 48);
                            break;
                        }
                    }
                }
            }
            point.x++;
            if (point.x >= endCol){ point.x = startCol; }
        }
        point.y++;
    }
}