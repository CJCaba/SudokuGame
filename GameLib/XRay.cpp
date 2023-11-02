/**
 * @file XRay.cpp
 * @author linja
 */

#include <random>

#include "pch.h"
#include "XRay.h"
#include "VisitorNumbers.h"

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
    std::uniform_real_distribution<> distributionX(GetX(), GetX() + GetWidth() - interact->GetWidth()); // Adjust the range as needed
    std::uniform_real_distribution<> distributionY(GetY(), GetY() + GetHeight() - interact->GetHeight()); // Adjust the range as needed

    bool overlap = false;

    do
    {
        overlap = false;
        double randomX = distributionX(randomSeed);
        double randomY = distributionY(randomSeed);

        if(mStomachItems.size() == 0)
        {
            interact->SetLocation(randomX, randomY);
            break;
        }

        for(const auto &loc : mStomachItems)
        {
            if(loc->HitTest(randomX, randomY))
            {
                overlap = true;
                break;
            }
//            else if(loc->GetX() - loc->GetWidth() < randomX ||
//                    loc->GetY() - loc->GetHeight() < randomY) //< Buffer for Bitmap hit
//            {
//                overlap = true;
//                break;
//            }
        }

        if(!overlap)
        {
            interact->SetLocation(randomX, randomY);
        }

    } while(overlap);

    mStomachItems.push_back(interact);
}

bool XRay::Check(InteractNumber* item)
{
    auto loc = find(begin(mStomachItems), end(mStomachItems), item);
    if (loc != std::end(mStomachItems))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void XRay::Remove(InteractNumber* item)
{
    auto loc = find(begin(mStomachItems), end(mStomachItems), item);
    if (loc != std::end(mStomachItems))
    {
        mStomachItems.erase(loc);
    }
}

InteractNumber* XRay::Find(int value)
{
    for (auto item : mStomachItems)
    {
        if(item->GetValue() == value)
        {
            return item;
        }
    }

    return nullptr;
}