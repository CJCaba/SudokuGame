/**
 * @file Container.cpp
 * @author Gerald Hoskins
 */

#include "pch.h"

#include <random>

#include "Container.h"
#include "Game.h"

using namespace std;

/**
 * Constructor
 * @param game The game this container is a member of
 * @param backImageFilename The name of the file that contains the back of the container
 * @param frontImageFilename The name of the file that contains the front of the container
 */
Container::Container(Game *game, const std::wstring &backImageFilename, const std::wstring &frontImageFilename) : mGame(game)
{
    mBackImage = make_unique<wxImage>(backImageFilename, wxBITMAP_TYPE_ANY);
    mFrontImage = make_unique<wxImage>(frontImageFilename, wxBITMAP_TYPE_ANY);
}

/**
 * Destructor
 */
Container::~Container()
{

}

/**
 * Adds an item to the container
 * @param item to add
 */
void Container::add(const shared_ptr<Item>& item)
{
    mItems.push_back(item);

    // Move location to be within container boundaries
    auto randomSeed = mGame->GetRandom();
    uniform_real_distribution<> distributionX(mX, mX + mBackImage->GetWidth());
    uniform_real_distribution<> distributionY(mY, mY + mBackImage->GetHeight());
    item->SetLocation(distributionX(randomSeed), distributionY(randomSeed));
}

/**
 * Pops the item out of the container. This will return nullptr if not found.
 * @param item Item to
 * @return
 */
void Container::release()
{
    auto randomSeed = mGame->GetRandom();

    // Distribute contained items across the screen
    for (const auto& item : mItems)
    {
        uniform_real_distribution<> distributionX(0, 100);//mGame->GetBackgroundImage()->GetWidth());
        uniform_real_distribution<> distributionY(0, 100);//mGame->GetBackgroundImage()->GetHeight());
        item->SetLocation(distributionX(randomSeed), distributionY(randomSeed));
    }

    // Empty the container
    mItems.clear();
}

void Container::Draw(const shared_ptr<wxGraphicsContext>& graphics)
{
    if(mBackBitmap.IsNull())
        mBackBitmap = graphics->CreateBitmapFromImage(*mBackImage);
    if (mFrontBitmap.IsNull())
        mFrontBitmap = graphics->CreateBitmapFromImage(*mFrontImage);

    // Draw the bottom bitmap
    int bottomImageWidth = mBackImage->GetWidth();
    int bottomImageHeight = mBackImage->GetHeight();
    graphics->DrawBitmap(mBackBitmap, GetX(), GetY(), bottomImageWidth, bottomImageHeight);

    // Draw contained items
    for (const auto& item : mItems)
    {
        item->Draw(graphics);
    }

    // Draw the top bitmap
    int topImageWidth = mFrontImage->GetWidth();
    int topImageHeight = mFrontImage->GetHeight();
    graphics->DrawBitmap(mBackBitmap, GetX(), GetY(), topImageWidth, topImageHeight);
}