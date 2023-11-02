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
 * @param game The game class the item is a part of
 * @param dec Pointer to a Declartion node containing basic information
 * @param item Pointer to an Item node containing position information
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

bool Item::OnBoard(wxPoint point)
{
    auto game = GetGame();

    int startCol = point.x;
    int endCol = point.x + 9;
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            if(HitTest(point.x * game->GetTileWidth(), point.y * game->GetTileHeight() )){
                return true;
            }
            point.x++;
            if(point.x >= endCol){ point.x = startCol; }
        }
        point.y++;
    }

    return false;
}
