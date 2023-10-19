/**
 * @file Game.cpp
 * @author Daniel Flanagan, Tyler Przybylo, and Jason Lin
 */

#include "pch.h"
#include "Game.h"
#include "Clock.h"
#include "Sparty.h"
#include "Declaration.h"
#include "DeclarationGiven.h"
#include "DeclarationInteract.h"
#include "DeclarationSparty.h"

using namespace std;

/// Path to Background Image (Hard Coded)
std::string backgroundFileName = "images/background.png";

/// Path to X-Ray Image (Hard Coded)
std::string xRayFileName = "images/xray.png";

// Delete this later, hardcoded until xml loading is figured out
std::wstring spartyHead = L"images/sparty-1.png";
std::wstring spartyMouth = L"images/sparty-2.png";

/**
 * Constructor for the game object
 */
Game::Game()
{
    mBackgroundImage = std::make_shared<wxImage>(backgroundFileName);
    mSparty = std::make_shared<Sparty>(this, spartyHead, spartyMouth);
    mXRayImage = std::make_shared<wxImage>(xRayFileName);

    auto clock = std::make_shared<Clock>(this);
    mClock = clock;
    mClock->Reset();
}

/**
 * Add an item to the game
 * @param item New item to add
 */
void Game::Add(std::shared_ptr<Item> item)
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
    //
    // Take Background Bitmap and Load Width & Height
    //
    if (mBackgroundBitmap.IsNull())
    {
        mBackgroundBitmap = graphics->CreateBitmapFromImage(*mBackgroundImage);
    }
    int backgroundWidth = mBackgroundImage->GetWidth();
    int backgroundHeight = mBackgroundImage->GetHeight();

    // Determine the size of the playing area in pixels
    // This is up to you...
    mPixelWidth = backgroundWidth;
    mPixelHeight = backgroundHeight;

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
    graphics->PopState();

    mPixelWidth *= mScale;
    mPixelHeight *= mScale;

    //
    // Draw in virtual pixels on the graphics context
    //
    // INSERT YOUR DRAWING CODE HERE

    //
    // Draws Background
    //
    graphics->DrawBitmap(mBackgroundBitmap,
                         mXOffset, mYOffset,
                         mPixelWidth,
                         mPixelHeight);

    //
    // Take X-Ray Image and BitMap
    // Draw X-Ray
    //
    if (mXRayBitmap.IsNull())
    {
        mXRayBitmap = graphics->CreateBitmapFromImage(*mXRayImage);
    }
    int xRayWidth = mXRayImage->GetWidth();
    int xRayHeight = mXRayImage->GetHeight();

    graphics->DrawBitmap(mXRayBitmap,
                         mXOffset + (30 * mScale),
                         mYOffset + ((backgroundHeight - xRayHeight) * mScale),
                         xRayWidth * mScale,
                         xRayHeight * mScale);

    //
    // Hard coded drawing sparty until the add items function is implemented
    //
    mSparty->Draw(graphics);


    //
    // Drawing a rectangle that is the playing area size
    // Draw a rectangle
    //


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

        double rectX = mXOffset + (mPixelWidth / 2) - (rectWidth / 2);
        double rectY = mYOffset + (mPixelHeight / 2) - (rectHeight / 2);

        graphics->DrawRectangle(rectX, rectY,rectWidth, rectHeight);

        wxFont bigFont(wxSize(75 * mScale, 75 * mScale),
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
        wxFont subFont(wxSize(50 * mScale, 50 * mScale),
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
        }
    }
    else
    {
        // Drawing Clock on Screen, should be Top Layer Drawing
        mClock->Draw(graphics);
    }


    // loop through items
    // if item is not in any containers
    // draw item

    // loop through containers
    // draw container (also draws contained items)

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

void Game::OnLeftDown(wxMouseEvent &event)
{
    double virtualX = ( event.GetX() - mXOffset ) / mScale;
    double virtualY = ( event.GetY() - mYOffset ) / mScale;

    if (!WithinWidth(virtualX))
        return;

    if (!WithinHeight(virtualY))
        return;

    mSparty->SetTarget( wxPoint(virtualX, virtualY) );
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

    if (dec != nullptr)
    {
        id = node->GetAttribute(L"id", L'0').ToStdString();
        mDeclarations[id] = dec;
        dec->XmlLoad(node);
    }
}

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