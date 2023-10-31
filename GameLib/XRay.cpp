/**
 * @file XRay.cpp
 * @author linja
 */

#include <random>

#include "pch.h"
#include "XRay.h"

using namespace std;

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
}

void XRay::Add(InteractNumber* interact)
{
    if (mStomachItems.size() >= mCapacity)
    {
        return;
    }

    auto game = GetGame();

    auto randomSeed = game->GetRandom();
    std::uniform_real_distribution<> distributionX(GetX(), GetX() + GetWidth()); // Adjust the range as needed
    std::uniform_real_distribution<> distributionY(GetY(), GetY() + GetHeight()); // Adjust the range as needed

    double randomX = distributionX(randomSeed);
    double randomY = distributionY(randomSeed);
    interact->SetLocation(randomX, randomY);

    mStomachItems.push_back(interact);
}