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
 * @param clock Reference to Analog Clock object
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
    int pixelWidth = backgroundWidth;
    int pixelHeight = backgroundHeight;

    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    graphics->PushState();
    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);
    graphics->PopState();

    //
    // Draw in virtual pixels on the graphics context
    //
    // INSERT YOUR DRAWING CODE HERE

    //
    // Draws Background
    //
    graphics->DrawBitmap(mBackgroundBitmap,
                         mXOffset, mYOffset,
                         backgroundWidth * mScale,
                         backgroundHeight * mScale);

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
    // Drawing a rectangle that is the playing area size
    // Draw a rectangle
    //
    graphics->PushState();
    graphics->DrawRectangle(0, 0, pixelWidth, pixelHeight);
    graphics->PopState();

    //
    // Hard coded drawing sparty until the add items function is implemented
    //
    mSparty->Draw(graphics);

    //
    // Drawing Clock on Screen
    // Draws text in corner of Game Rectangle
    //
    wxFont font(wxSize(50 * mScale, 50 * mScale),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, wxColour(*wxWHITE));

    std::string analog = mClock->GetMinutes() + ":" + mClock->GetSeconds();
    graphics->DrawText(analog, mXOffset + (50 * mScale), mYOffset + (20 * mScale));

    //
    // Hard coded drawing sparty until the add items function is implemented
    //
    mSparty->Draw(graphics);

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
    }
}