/**
 * @file Game.cpp
 * @author Daniel Flanagan and Tyler Przybylo
 */

#include "pch.h"
#include "Game.h"

using namespace std;

/**
 * Constructor for the game object
 */
 Game::Game()
{
     // mBackgroundImage = std::make_shared<wxImage>(L"images/background.png");
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
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    // Determine the size of the playing area in pixels
    // This is up to you...
    int pixelWidth = 48;
    int pixelHeight = 48;

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

    //
    // Draw in virtual pixels on the graphics context
    //
    // INSERT YOUR DRAWING CODE HERE

    // Broken background code
//     if (mBackgroundBitmap.IsNull())
//    {
//        mBackgroundBitmap = graphics->CreateBitmapFromImage(*mBackgroundImage);
//    }
//    int backgroundWidth = mBackgroundImage->GetWidth();
//    int backgroundHeight = mBackgroundImage->GetHeight();
//    graphics->DrawBitmap(mBackgroundBitmap, 0, 0, backgroundWidth, backgroundHeight);

    //
    // Drawing a rectangle that is the playing area size
    // Draw a rectangle
    wxBrush background(*wxRED);

    graphics->SetBrush(background);
    graphics->DrawRectangle(0, 0, pixelWidth, pixelHeight);

    graphics->PopState();

}

