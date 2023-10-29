/**
 * @file Sparty.cpp
 * @author Tyler Przybylo
 */

#include "pch.h"
#include "Sparty.h"

/// Character speed in pixels per second
const double MaxSpeed = 400.00;

/// The time for an eating cycles in seconds
const double EatingTime = 0.5;

/// The time for a headbutt cycle in seconds
const double HeadbuttTime = 0.5;

Sparty::Sparty(Game *game, wxXmlNode * dec, wxXmlNode* item) : Item(game, dec, item)
{
    std::wstring filename2 = L"images/" + dec->GetAttribute("image2", "").ToStdWstring();
    mMouthImage = std::make_unique<wxImage>(filename2, wxBITMAP_TYPE_ANY);
    dec->GetAttribute("head-pivot-angle", "0").ToDouble(&mHeadPivotAngle);
    dec->GetAttribute("head-pivot-x", "0").ToInt(&mHeadPivot.x);
    dec->GetAttribute("head-pivot-y", "0").ToInt(&mHeadPivot.y);
    dec->GetAttribute("mouth-pivot-angle", "0").ToDouble(&mMouthPivotAngle);
    dec->GetAttribute("mouth-pivot-x", "0").ToInt(&mMouthPivot.x);
    dec->GetAttribute("mouth-pivot-y", "0").ToInt(&mMouthPivot.y);
    dec->GetAttribute("target-x", "0").ToInt(&mTargetOffset.x);
    dec->GetAttribute("target-y", "0").ToInt(&mTargetOffset.y);
}

/**
 * Draws the item.
 * @param graphics Graphics context to draw the item on.
 */
void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Mouth drawing code
    if(mMouthBitmap.IsNull()){
        mMouthBitmap = graphics->CreateBitmapFromImage(*mMouthImage);
    }

    // Saving useful values
    int itemWid = mMouthImage->GetWidth();
    int itemHeight = mMouthImage->GetHeight();
    double headPivotX = GetX() + mHeadPivot.x;
    double headPivotY = GetY() + mHeadPivot.y;
    double mouthPivotX = GetX() + mMouthPivot.x;
    double mouthPivotY = GetY() + mMouthPivot.y;

    graphics->PushState();

    graphics->Translate(headPivotX, headPivotY);
    graphics->Rotate(mHeadAngle);
    graphics->Translate(-headPivotX, -headPivotY);

    // Head gets drawn first if 1
    if (mFront == 1)
    {
        Item::Draw(graphics);
    }

    graphics->PushState();

    graphics->Translate(mouthPivotX, mouthPivotY);
    graphics->Rotate(mMouthAngle);
    graphics->Translate(-mouthPivotX, -mouthPivotY);

    graphics->DrawBitmap(mMouthBitmap, GetX(), GetY(), itemWid, itemHeight);

    graphics->PopState();

    // Head gets drawn last if 2
    if (mFront == 2)
    {
        Item::Draw(graphics);
    }

    graphics->PopState();
}

/**
 * Handle updates in time of Sparty.
 * @param elapsed The time since the last update.
*/
void Sparty::Update(double elapsed)
{
    auto game = GetGame();

    double deltaX = mTargetPoint.x - Item::GetX();
    double deltaY = mTargetPoint.y - Item::GetY();

    // Calculate the length of the vector
    double length = sqrt(deltaX * deltaX + deltaY * deltaY);

    // If the remaining distance is smaller than the distance Sparty can travel this frame
    if (length <= MaxSpeed * elapsed)
    {
        SetLocation(mTargetPoint.x, mTargetPoint.y);
    }
    else
    {
        // Calculate the scaling factor to reach the desired distance
        double scaleFactor = MaxSpeed * elapsed / length;

        // Calculate the new point's coordinates
        double newX = Item::GetX() + deltaX * scaleFactor;
        double newY = Item::GetY() + deltaY * scaleFactor;

        if (newX > double( game->GetWidth() - (GetWidth()/2) ))
        {
            newX = double(game->GetWidth() - (GetWidth()/2) );
        }

        if (newY > double(game->GetHeight() - GetHeight()) )
        {
            newY = double(game->GetHeight() - GetHeight());
        }

        SetLocation(newX, newY);
    }

    if (mIsEating)
    {
        mElapsedTimeEating += elapsed;
        if (mElapsedTimeEating < EatingTime / 2)
            mMouthAngle = mElapsedTimeEating / (EatingTime / 2) * mMouthPivotAngle;
        else
            mMouthAngle = (EatingTime - mElapsedTimeEating) / (EatingTime / 2) * mMouthPivotAngle;

        if (mElapsedTimeEating >= EatingTime)
        {
            mElapsedTimeEating = 0.0;
            mIsEating = false;
            mMouthAngle = 0.0;
        }
    }

    if (mIsHeadButting)
    {
        mElapsedTimeHeadButting += elapsed;
        if (mElapsedTimeHeadButting < HeadbuttTime / 2)
            mHeadAngle = mElapsedTimeHeadButting / (HeadbuttTime / 2) * mHeadPivotAngle;
        else
            mHeadAngle = (HeadbuttTime - mElapsedTimeHeadButting) / (HeadbuttTime / 2) * mHeadPivotAngle;

        if (mElapsedTimeHeadButting >= HeadbuttTime)
        {
            mElapsedTimeHeadButting = 0.0;
            mIsHeadButting = false;
            mHeadAngle = 0.0;
        }
    }

}