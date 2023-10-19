/**
 * @file Item.cpp
 * @author Tyler Przybylo,
 * @author Jaden Cabansag
 */

#include "pch.h"

#include "Item.h"

using namespace std;

/**
 * Constructor
 * @param Game The game this item is a member of
 * @param filename The name of the image file
 */
Item::Item(Game *game, const wstring &filename) : mGame(game)
{
    mItemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
};

/**
* Destructor
*/
Item::~Item()
{

}

/**
 * Draws the item.
 * @param graphics Graphics context to draw the item on.
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Checks if bitmap is empty, then imports the image
    if(mItemBitmap.IsNull()){
        mItemBitmap = graphics->CreateBitmapFromImage(*mItemImage);
    }
    // Now it is okay to draw that bitmap.
    int itemWid = mItemImage->GetWidth() * mGame->GetScale();
    int itemHeight = mItemImage->GetHeight() * mGame->GetScale();
    double virtualX = mGame->GetXOffset() + GetX() * mGame->GetScale();
    double virtualY = mGame->GetYOffset() + GetY() * mGame->GetScale();
    graphics->DrawBitmap(mItemBitmap, virtualX, virtualY, itemWid, itemHeight);
}
