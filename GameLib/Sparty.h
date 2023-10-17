/**
 * @file Sparty.h
 * @author Tyler Przybylo
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

    wxPoint mMouthPivot; ///< Contains the x and y information for the mouth pivot point
    wxPoint mHeadPivot; ///< Contains the x and y information for the head pivot point

    double mMouthAngle; ///< Angle of the mouth in radians

    wxPoint mTarget; ///< Contains the x and y information for where the player last clicked (sparty goes to that point)

public:
    /// Default constructor (disabled)
    Sparty() = delete;

    /// Copy constructor (disabled)
    Sparty(const Sparty &) = delete;

    /// Assignment operator
    void operator=(const Sparty &) = delete;

    /// Constructor
    Sparty(Game *game, const std::wstring &filename1, const std::wstring &filename2);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
};

#endif //ARES_GAMELIB_SPARTY_H
