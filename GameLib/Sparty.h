/**
 * @file Sparty.h
 * @author Tyler Przybylo
 * @author Jerry Hoskins
 *
 * Class for Sparty
 */

#ifndef ARES_GAMELIB_SPARTY_H
#define ARES_GAMELIB_SPARTY_H

#include "Item.h"

/**
 * Class for Sparty
 */
class Sparty : public Item
{
private:
    int mFront = 1; ///< Which sparty to draw on top (1 (Head) or 2 (Mouth)). Used for animations

    /// The image for this tile
    std::unique_ptr<wxImage> mMouthImage;

    /// The bitmap for this tile
    wxGraphicsBitmap mMouthBitmap;

    /// Flag for if Sparty is eating
    bool mIsEating = false;

    /// How long Sparty has been eating
    double mElapsedTimeEating = 0.0;

    /// Flag for if Sparty is head butting
    bool mIsHeadButting = false;

    /// How long Sparty has been head butting
    double mElapsedTimeHeadButting = 0.0;

    /// The final angle of the mouth pivot in radians
    double mMouthPivotAngle;

    /// The final angle of the head pivot in radians
    double mHeadPivotAngle;

    wxPoint mMouthPivot; ///< Contains the x and y information for the mouth pivot point
    wxPoint mHeadPivot; ///< Contains the x and y information for the head pivot point

    double mMouthAngle; ///< Angle of the mouth in radians
    double mHeadAngle; ///< Angle of the head in radians

    wxPoint mTargetPoint; ///< Contains the x and y information for where the player last clicked (sparty goes to that point)
    wxPoint mTargetOffset = wxPoint(72, 24); ///< Contains the x and y offset from the target point


public:
    /// Default constructor (disabled)
    Sparty() = delete;

    /// Copy constructor (disabled)
    Sparty(const Sparty &) = delete;

    /// Assignment operator
    void operator=(const Sparty &) = delete;

    /// Constructor
    Sparty(Game *game, const std::wstring &filename1, const std::wstring &filename2);

    /**
     * Move Sparty to given point.
     * @param target The point Sparty should travel to.
     */
    void MoveToPoint(wxPoint target) { mTargetPoint = target; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elapsed);

    /**
     * Make Sparty eat.
     */
    void MakeEat() { mIsEating = true; }

    /**
     * Make Spaty headbutt.
     */
     void MakeHeadButt() { mIsHeadButting = true; }

     /**
      * Getter for the target offset.
      */
      wxPoint GetTargetOffset() { return mTargetOffset; }
};

#endif //ARES_GAMELIB_SPARTY_H
