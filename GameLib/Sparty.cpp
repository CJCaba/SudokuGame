/**
 * @file Sparty.cpp
 * @author Tyler Przybylo
 */

#include "pch.h"

#include "Sparty.h"

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
    // Head gets drawn first if 1
    if (mFront == 1)
    {
        Item::Draw(graphics);
    }

    // Mouth drawing code
    if(mMouthBitmap.IsNull()){
        mMouthBitmap = graphics ->CreateBitmapFromImage(*mMouthImage);
    }
    // Now it is okay to draw that bitmap.
    int itemWid = mMouthImage->GetWidth();
    int itemHeight = mMouthImage->GetHeight();
    graphics->DrawBitmap(mMouthBitmap, GetX(), GetY(), itemWid, itemHeight);

    // Head gets drawn last if 2
    if (mFront == 2)
    {
        Item::Draw(graphics);
    }
}