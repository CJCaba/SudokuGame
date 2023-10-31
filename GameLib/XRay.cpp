/**
 * @file XRay.cpp
 * @author linja
 */

#include "pch.h"
#include "XRay.h"

/**
 * Constructor
 * @param game The game class the item is a part of
 * @param dec Pointer to a Declartion node containing basic information
 * @param item Pointer to an Item node containing position information
 */
XRay::XRay(Game *game, wxXmlNode * dec, wxXmlNode* item) : Item(game, dec, item)
{
}

/**
 * Draw the XRay onto the board
 * @param graphics The graphics context to draw on
 */
void XRay::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Item::Draw(graphics);

    for(auto &item : mStomachItems)
        item->SetLocation(0,0);
}

void XRay::Add(InteractNumber* interact)
{
    if (mStomachItems.size() >= mCapacity)
    {
        return;
    }

    mStomachItems.push_back(interact);
}