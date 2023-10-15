/**
 * @file Container.cpp
 * @author Gerald Hoskins
 */

#include "pch.h"

#include <random>

#include "Container.h"
#include "Game.h"

/**
 * Adds an item to the container
 * @param item to add
 */
void Container::add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Pops the item out of the container. This will return nullptr if not found.
 * @param item Item to
 * @return
 */
void Container::release()
{
    // Distribute contained items across the screen
    for (auto item : mItems)
    {
        auto game = item->GetGame();
        auto randomSeed = game->GetRandom();
        std::uniform_real_distribution<> distributionX(0, 100);//game->GetBackgroundImage()->GetWidth());
        std::uniform_real_distribution<> distributionY(0, 100);//game->GetBackgroundImage()->GetHeight());
        item->SetLocation(distributionX(randomSeed), distributionY(randomSeed));
    }

    // Empty the container
    mItems.clear();
}

void Container::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(mBottomBitmap.IsNull())
    {
        mBottomBitmap = graphics->CreateBitmapFromImage(*mBottomImage);
    }
    if (mTopBitmap.IsNull())
        mTopBitmap = graphics->CreateBitmapFromImage(*mTopImage);

    // Draw the bottom bitmap
    int bottomImageWidth = mBottomImage->GetWidth();
    int bottomImageHeight = mBottomImage->GetHeight();
    graphics->DrawBitmap(mBottomBitmap, GetX(), GetY(), bottomImageWidth, bottomImageHeight);

    // Draw contained items
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }

    // Draw the top bitmap
    int topImageWidth = mTopImage->GetWidth();
    int topImageHeight = mTopImage->GetHeight();
    graphics->DrawBitmap(mBottomBitmap, GetX(), GetY(), topImageWidth, topImageHeight);
}