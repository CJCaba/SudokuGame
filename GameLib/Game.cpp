/**
 * @file Game.cpp
 * @author Daniel Flanagan, Tyler Przybylo, and Jason Lin
 */

#include "pch.h"
#include "Game.h"
#include "Clock.h"
#include "Sparty.h"
#include "XRay.h"
#include "Declaration.h"
#include "DeclarationGiven.h"
#include "DeclarationInteract.h"
#include "DeclarationSparty.h"
#include "DeclarationBackground.h"
#include "DeclarationContainer.h"
#include "Number.h"
#include "GivenNumber.h"
#include "InteractNumber.h"
#include "Solution.h"
#include "Background.h"


using namespace std;

// Path to Background Image (Hard Coded)
std::wstring backgroundFileName = L"images/background.png";

// Path to X-Ray Image (Hard Coded)
std::wstring xRayFileName = L"images/xray.png";

// Delete this later, hardcoded until xml loading is figured out
std::wstring spartyHead = L"images/sparty-1.png";
std::wstring spartyMouth = L"images/sparty-2.png";

// Level 1
std::wstring level1 = L"LevelFiles/level1.xml";
std::wstring level2 = L"LevelFiles/level2.xml";

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

    mSparty = std::make_shared<Sparty>(this, spartyHead, spartyMouth);
    mXRay = std::make_shared<XRay>(this, xRayFileName);

    mClock = std::make_shared<Clock>(this);

    mClock->Reset();

    mGameSolution = std::make_shared<Solution>();
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

    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
    // loop through items
    // if item is not in any containers
    // draw item

    // loop through containers
    // draw container (also draws contained items)

    // Hard Code Draw X-Ray
    mXRay->Draw(graphics);

    // Hard coded drawing sparty until the add items function is implemented
    mSparty->Draw(graphics);


    //
    // Checks if level is booting up
    //
    if(mStartUp)
    {
        //
        // Draws brief tutorial screen
        //

        // Draw tutorial box
        graphics->PushState();
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

        // Draw Title
        double titleWidth, titleHeight;
        graphics->GetTextExtent(L"Level 1 Begin", &titleWidth, &titleHeight);
        graphics->DrawText(L"Level 1 Begin",
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

        graphics->PopState();

        // After 3 seconds, remove tutorial and start game
        if(mClock->GetSeconds() == "03")
        {
            mStartUp = false;
            mClock->Reset();

            if (mItems.empty())
                //Load(level1);
                //Load(level2);
                Load(mCurrentLevel);

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
    mClock->AddTime(elapsed);
    mSparty->Update(elapsed);
}

/**
 * Handle the left mouse button down event
 * @param event The mouse event
 */
void Game::OnLeftDown(wxMouseEvent &event)
{

    wxPoint targetOffset = mSparty->GetTargetOffset();

    double virtualX = ( event.GetX() - targetOffset.x - mXOffset ) / mScale;
    double virtualY = ( event.GetY() - targetOffset.y - mYOffset ) / mScale;

    if (!WithinWidth(virtualX))
        return;

    if (!WithinHeight(virtualY))
        return;

    mSparty->MoveToPoint( wxPoint(virtualX, virtualY) );
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
    }
    else if (keyCode == 66) // ASCII 66 = B
    {
        mSparty->MakeHeadButt();
    }
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

    int tileWidth;
    int tileHeight;
    root->GetAttribute("tilewidth", "1").ToInt(&tileWidth);
    root->GetAttribute("tileheight", "1").ToInt(&tileHeight);
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
                XmlItem(decChild, tileWidth, tileHeight);
            }
        }
        // Handles loading the game's solution
        else if (name == L"game")
        {
            mGameSolution ->LoadSolution(child);
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
    mItems.clear();
    mContainers.clear();
    mDeclarations.clear();
    mBackgroundImage->Clear();
    mBackgroundBitmap.UnRef();
}

void Game::XmlDeclare(wxXmlNode *node){
    shared_ptr<Declaration> dec;
    string id;

    auto name = node->GetName();

    if (name == L"given")
    {
        dec = make_shared<DeclarationGiven>(this);
    }

    if (name == L"digit")
    {
        dec = make_shared<DeclarationInteract>(this);
    }

    if (name == L"sparty")
    {
        dec = make_shared<DeclarationSparty>(this);
    }

    if (name == L"background"){
        dec = make_shared<DeclarationBackground>(this);
    }

    if (name == L"container"){
        dec = make_shared<DeclarationContainer>(this);
    }

    if (dec != nullptr)
    {
        id = node->GetAttribute(L"id", L'0').ToStdString();
        mDeclarations[id] = dec;
        dec->XmlLoad(node);
    }
}

void Game::XmlItem(wxXmlNode *node, double tileWidth, double tileHeight){
    shared_ptr<Item> item;
    auto name = node->GetName();
    auto itemID = node->GetAttribute("id", "").ToStdString();
    auto itemDeclaration = mDeclarations[itemID];

    if(name == "given")
    {
        item = std::make_shared<GivenNumber>(this, L"images/" + itemDeclaration->GetImage());

    }

    if(name == "digit")
    {
        item = std::make_shared<InteractNumber>(this, L"images/" + itemDeclaration->GetImage());
    }

    if(name == "background")
    {
        item = make_shared<Background>(this, L"images/" + itemDeclaration->GetImage());
        double x,y, height;
        node->GetAttribute("col", "0").ToDouble(&x);
        node->GetAttribute("row", "0").ToDouble(&y);
        height = itemDeclaration->GetHeight();
        item->SetLocation(x * tileHeight, (y + 1) * tileHeight - height);
        AddItem(item);
    }

    if(item && name != "background")
    {
        double x;
        double y;

        node->GetAttribute("col", "0").ToDouble(&x);
        node->GetAttribute("row", "0").ToDouble(&y);

        item->SetLocation(x * tileHeight, y * tileHeight);

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
}