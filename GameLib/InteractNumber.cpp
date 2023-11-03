/**
 * @file InteractNumber.cpp
 * @author Jaden Cabansag
 */

#include "pch.h"
#include "InteractNumber.h"

/**
 * Constructor
 * @param game The game class the item is a part of
 * @param dec Pointer to a Declartion node containing basic information
 * @param item Pointer to an Item node containing position information
 */
InteractNumber::InteractNumber(Game *game, wxXmlNode * dec, wxXmlNode* item) :
    Number(game, dec, item)
{
}
void InteractNumber::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mXRayFlag)
    {
        // Now it is okay to draw that bitmap.
        double itemWid = GetWidth();
        double itemHeight = GetHeight();
        graphics->DrawBitmap(GetBitMap(), GetX(), GetY(), itemWid * 0.6, itemHeight * 0.6);
    }
    else
        Item::Draw(graphics);
}
