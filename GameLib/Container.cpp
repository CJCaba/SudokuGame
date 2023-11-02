/**
 * @file Container.cpp
 * @author Gerald Hoskins
 */

#include "pch.h"

#include <random>

#include "Container.h"
#include "Game.h"
#include "InteractNumber.h"

using namespace std;

/**
 * Constructor
 * @param game The game this container is a member of
 * @param dec The declaration node containing all the information to create a basic Container
 * @param item The item node containing the location information for this specific Container
 */
Container::Container(Game *game, wxXmlNode *dec, wxXmlNode* item) : Item(game, dec, item)
{   auto backImageFilename = dec->GetAttribute("image", "");
    auto frontImageFilename = dec->GetAttribute("front", "");
    auto id = dec->GetAttribute("id", "").ToStdString();
    mBackImage = make_unique<wxImage>(L"images/" + backImageFilename, wxBITMAP_TYPE_ANY);
    mFrontImage = make_unique<wxImage>(L"images/" + frontImageFilename, wxBITMAP_TYPE_ANY);
    auto child = item->GetChildren();
    for (;child; child=child->GetNext()){
        auto id = child->GetAttribute("id", "0").ToStdString();
        auto itemDec = game->GetDec()[id];
        auto numItem = std::make_shared<InteractNumber>(game, itemDec, child);
        double x, y;
        child->GetAttribute("col", "").ToDouble(&x);
        child->GetAttribute("row", "").ToDouble(&y);
        numItem->SetLocation(x * game->GetTileWidth(), y * game->GetTileHeight());
        mItems.push_back(numItem);
    }
}

/**
 * Adds an item to the container
 * @param item to add
 */
void Container::Add(const shared_ptr<Item>& item)
{
    mItems.push_back(item);

    // Move location to be within container boundaries
    auto randomSeed = mGame->GetRandom();
    uniform_real_distribution<> distributionX(mX, mX + mBackImage->GetWidth());
    uniform_real_distribution<> distributionY(mY, mY + mBackImage->GetHeight());
    item->SetLocation(distributionX(randomSeed), distributionY(randomSeed));
}

/**
 * Moves contained items to random locations
 * across the screen, then clears the container.
 */
void Container::Release()
{
    auto game = GetGame();
    auto randomSeed = game->GetRandom();

    // Distribute contained items across the screen
    for (const auto& item : mItems)
    {
        uniform_real_distribution<> distributionX(GetX() - (game->GetTileWidth()*2),
                                                  GetX() + GetWidth() + game->GetTileWidth());
        uniform_real_distribution<> distributionY(GetY() - (game->GetTileHeight()*2),
                                                  GetY());
        item->SetLocation(distributionX(randomSeed), distributionY(randomSeed));
        game->AddItem(item);
    }

    // Empty the container
    mItems.clear();
}

/**
 * Draw the container.
 * @param graphics Graphics context to draw the container on.
 */
void Container::Draw(shared_ptr<wxGraphicsContext> graphics)
{

//    if(mBackBitmap.IsNull())
//        mBackBitmap = graphics->CreateBitmapFromImage(*mBackImage);
    Item::Draw(graphics);
    if (mFrontBitmap.IsNull())
        mFrontBitmap = graphics->CreateBitmapFromImage(*mFrontImage);

    // Draw the bottom bitmap
//    int bottomImageWidth = mBackImage->GetWidth();
//    int bottomImageHeight = mBackImage->GetHeight();
//    graphics->DrawBitmap(mBackBitmap, GetX(), GetY(), bottomImageWidth, bottomImageHeight);

    // Draw contained items
    for (const auto& item : mItems)
    {
        item->Draw(graphics);
    }

    // Draw the top bitmap
    int topImageWidth = mFrontImage->GetWidth();
    int topImageHeight = mFrontImage->GetHeight();
    graphics->DrawBitmap(mFrontBitmap, GetX(), GetY(), topImageWidth, topImageHeight);
}