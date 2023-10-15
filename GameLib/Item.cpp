/**
 * @file Item.cpp
 * @author Tyler Przybylo
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
void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(mItemBitmap.IsNull()){
        mItemBitmap = graphics ->CreateBitmapFromImage(*mItemImage);
    }
    // Now it is okay to draw that bitmap.
    int itemWid = mItemImage->GetWidth();
    int itemHeight = mItemImage->GetHeight();
    graphics->DrawBitmap(mItemBitmap, GetX(), GetY(), itemWid, itemHeight);
}
