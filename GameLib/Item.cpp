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
Item::Item(Game *game, wxXmlNode * dec, wxXmlNode* item) : mGame(game)
{
    auto name = dec->GetName().ToStdString();
    mID = item->GetAttribute("id", "").ToStdString();
    wstring filename;
    if (name == "sparty")
    {
        filename = L"images/" + dec->GetAttribute("image1", "").ToStdWstring();;
    }
    else
    {
        filename = L"images/" + dec->GetAttribute("image", "").ToStdWstring();
    }

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
        mItemBitmap = graphics->CreateBitmapFromImage(*mGame->GetImage(mID));
    }

    // Now it is okay to draw that bitmap.
    double itemWid = GetWidth();
    double itemHeight = GetHeight();
    graphics->DrawBitmap(mItemBitmap, GetX(), GetY(), itemWid, itemHeight);
}
