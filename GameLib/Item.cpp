/**
 * @file Item.cpp
 * @author Tyler Przybylo,
 * @author Jaden Cabansag
 */

#include "pch.h"
#include "Item.h"

// Hard Coded Attributes
const double tileOffset = 96;

using namespace std;

/**
 * Constructor
 * @param game The game this item is a member of
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
    double itemWid = mItemImage->GetWidth();
    double itemHeight = mItemImage->GetHeight();
    graphics->DrawBitmap(mItemBitmap, GetX(), GetY(), itemWid, itemHeight);
}
