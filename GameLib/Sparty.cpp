/**
 * @file Sparty.cpp
 * @author Tyler Przybylo
 */

#include "pch.h"
#include "Sparty.h"

/// Character speed in pixels per second
const double MaxSpeed = 400.00;

/// The time for an eating cycles in seconds
const double EatingTime = 0.5;

/// The time for a headbutt cycle in seconds
const double HeadbuttTime = 0.5;

Sparty::Sparty(Game *game, const std::wstring &filename1, const std::wstring &filename2) : Item(game, filename1)
{
    mMouthImage = std::make_unique<wxImage>(filename2, wxBITMAP_TYPE_ANY);
}

/**
 * Draws the item.
 * @param graphics Graphics context to draw the item on.
 */
void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto game = Item::GetGame();

    // Head gets drawn first if 1
    if (mFront == 1)
    {
        Item::Draw(graphics);
    }

    // Mouth drawing code
    if(mMouthBitmap.IsNull()){
        mMouthBitmap = graphics->CreateBitmapFromImage(*mMouthImage);
    }
    // Now it is okay to draw that bitmap.
    int itemWid = mMouthImage->GetWidth() * game->GetScale();
    int itemHeight = mMouthImage->GetHeight() * game->GetScale();
    double virtualX = game->GetXOffset() + GetX() * game->GetScale();
    double virtualY = game->GetYOffset() + GetY() * game->GetScale();
    graphics->DrawBitmap(mMouthBitmap, virtualX, virtualY, itemWid, itemHeight);

    // Head gets drawn last if 2
    if (mFront == 2)
    {
        Item::Draw(graphics);
    }
}

/**
 * Handle updates in time of our fish.
 * @param elapsed The time since the last update.
*/
void Sparty::Update(double elapsed)
{
    double deltaX = mTarget.x - GetX();
    double deltaY = mTarget.y - GetY();

    // Calculate the length of the vector
    double length = sqrt(deltaX * deltaX + deltaY * deltaY);

    // If the remaining distance is smaller than the distance Sparty can travel this frame
    if (length <= MaxSpeed * elapsed)
    {
        SetLocation(mTarget.x, mTarget.y);
    }
    else
    {
        // Calculate the scaling factor to reach the desired distance
        double scaleFactor = MaxSpeed * elapsed / length;

        // Calculate the new point's coordinates
        double newX = GetX() + deltaX * scaleFactor;
        double newY = GetY() + deltaY * scaleFactor;

        SetLocation(newX, newY);
    }
}