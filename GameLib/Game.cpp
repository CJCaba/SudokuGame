/**
 * @file Game.cpp
 * @author Daniel Flanagan, Tyler Przybylo, and Jason Lin
 */

#include "pch.h"
#include "Game.h"
#include "Clock.h"

using namespace std;

/// Path to Background Image (Hard Coded)
std::string backgroundFileName = "images/background.png";

/// Path to X-Ray Image (Hard Coded)
std::string xRayFileName = "images/xray.png";

/**
 * Constructor for the game object
 */
Game::Game()
{
    mBackgroundImage = std::make_shared<wxImage>(backgroundFileName);
    mXRayImage = std::make_shared<wxImage>(xRayFileName);

    auto clock = std::make_shared<Clock>(this);
    mClock = clock;
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
    //graphics->PushState();
    //graphics->DrawRectangle(0, 0, pixelWidth, pixelHeight);
    //graphics->PopState();

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
void Game::OnUpdate(double elapsed, long time)
{
    mClock->SetTime(time);
}

