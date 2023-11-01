/**
 * @file Game.cpp
 * @author Daniel Flanagan, Tyler Przybylo, and Jason Lin
 */

#include "pch.h"
#include "Game.h"
#include "Clock.h"
#include "Sparty.h"
#include "XRay.h"
#include "Number.h"
#include "GivenNumber.h"
#include "InteractNumber.h"
#include "Solution.h"
#include "Container.h"
#include "Background.h"

#include "InteractiveItems.h"
#include "VisitorNumbers.h"
#include "XRayVisitor.h"
#include "ContainerVisitor.h"

using namespace std;

// Path to Background Image (Hard Coded)
std::wstring backgroundFileName = L"images/background.png";

// Level 1
std::wstring level1 = L"LevelFiles/level1.xml";

// Hard Coded Level 1 Attributes
double gameWidth = 20;
double gameHeight = 15;
const double tileSize = 48;

/**
 * Constructor for the game object
 */
Game::Game()
{
    mBackgroundImage = std::make_shared<wxImage>(backgroundFileName, wxBITMAP_TYPE_ANY);
    mGameSolution = std::make_shared<Solution>();
    mClock = std::make_shared<Clock>(this);
    mClock->Reset();

    mCurrentLevel = L"LevelFiles/level1.xml";
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
    mPixelWidth = gameWidth * tileSize;
    mPixelHeight = gameHeight * tileSize;

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

    // loop through items
    // if item is not in any containers
    // draw item
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }


    //
    // Checks if level is booting up
    //
    if(mStartUp)
    {
        //
        // Draws brief tutorial screen
        //

        // Draw tutorial box
        TutorialPrompt(graphics);

        // After 3 seconds, remove tutorial and start game
        if(mClock->GetSeconds() == "03")
        {
            mStartUp = false;
            mClock->Reset();

            if (mItems.empty())
                Load(level1);
        }
    }
    else
    {
        // Drawing Clock on Screen, should be Top Layer Drawing
        mClock->Draw(graphics);
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
    // Implement Building the Virtual Solution Board
    if (!mStartUp){
        UpdateBoard();
        LevelSolutionCorrect();
    }
}

void Game::OnLeftDown(wxMouseEvent &event)
{
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
        item = std::make_shared<XRay>(this, itemDeclaration, node);
    }

    if(name == "sparty")
    {
        mSparty = std::make_shared<Sparty>(this, itemDeclaration, node);
        item = mSparty;
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
    mCurrentLevel = filename;
    mClock->Reset();
    Load(filename);
}

/**
 * Handle the key down event
 * @param event The key event
 */
void Game::OnKeyDown(wxKeyEvent &event)
{
    int keyCode = event.GetKeyCode();

    if (keyCode == WXK_SPACE)
    {
        mSparty->MakeEat();
        if (!mSparty->IsMoving())
        {
            auto target = mSparty->GetTargetPoint();

            // Visitor creating an array of interact numbers
            InteractiveItems visitorOne;
            Accept(&visitorOne);

            // Visitor finding xray
            XRayVisitor visitorTwo;
            Accept(&visitorTwo);

            auto redNumbers = visitorOne.InteractFound();
            auto xRay = visitorTwo.XRayFound();

            for (const auto& item : redNumbers) {
                // if item is found, add to xray and break
                if (item->HitTest(target))
                {
                    xRay->Add(item);
                    break;
                }
            }
        }
    }
    else if (keyCode == 66) // ASCII 66 = B
    {
        mSparty->MakeHeadButt();
        if (!mSparty->IsMoving())
        {
            auto target = mSparty->GetTargetPoint();

            // Visitor finding
            ContainerVisitor visitor;
            Accept(&visitor);

            auto container = visitor.ContainerFound();

            for (auto item : container) {
                if (item->HitTest(target))
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
    if (mCurrentLevel == L"LevelFiles/level1.xml")
    {
        return L"Level 1 Begin";
    }
    else if (mCurrentLevel == L"LevelFiles/level2.xml")
    {
        return L"Level 2 Begin";
    }
    else if (mCurrentLevel == L"LevelFiles/level3.xml")
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
    graphics->SetFont(bigFont, wxColour(78,91,49));

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
 * Getter to return a specific image file loaded from our Declarations
 * @param id The id attributed to a specific image
 * @return Pointer to wxImage
 */
std::shared_ptr<wxImage> Game::GetImage(const string& id){
    return mImages[id];
}

void Game::Accept(Visitor *visitor)
{
    for (const auto &item : mItems)
    {
        item->Accept(visitor);
    }
}


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
                if (item->HitTest(point * 48)){
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
    int** expectedSolution = mGameSolution->getSolutionNumbers();
    bool arraysAreIdentical = true;
    for (int i = 0; i < 9 && arraysAreIdentical; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (expectedSolution[i][j] != mSolution[i][j]) {
                arraysAreIdentical = false;
                break;
            }
        }
    }
    if (arraysAreIdentical) {
        mLevelWon = true;
    }
}
