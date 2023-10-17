/**
 * @file Game.h
 * @authors Daniel Flanagan, Tyler Przybylo, and Jason Lin
 *
 * Class that implements the game
 */

#ifndef ARES_GAMELIB_GAME_H
#define ARES_GAMELIB_GAME_H

#include <random>
#include <vector>
#include <memory>
#include <map>
#include <wx/graphics.h>

#include "Item.h"
#include "Container.h"
#include "Declaration.h"

class Clock;
#include "Sparty.h"

/**
 * Implements a game class with necessary items
 */
class Game
{
private:
    /// Collection of items within the game
    std::vector<std::shared_ptr<Item>> mItems;

    /// Collection of containers within the game
    std::vector<std::shared_ptr<Container>> mContainers;

    std::shared_ptr<Sparty> mSparty;

    std::shared_ptr<wxImage> mBackgroundImage;  ///< Background image to use

    wxGraphicsBitmap mBackgroundBitmap; ///< The background bitmap

    /// X-Ray Image to use
    std::shared_ptr<wxImage> mXRayImage;

    /// X-Ray Image as Bitmap for wx
    wxGraphicsBitmap mXRayBitmap;

    /// The current scale of our game made in comparison to our window
    double mScale = 0;

    /// The amount to shift the graphics object in the x direction
    double mXOffset = 0;

    /// The amount to shift the graphics object in the y direction
    double mYOffset = 0;

    /// Random number generator
    std::mt19937 mRandom;

    /// Object containing the runtime of the game
    std::shared_ptr<Clock> mClock;

    /// Map of Declarations, with IDs as keys
    map<string, Declaration> mDeclarations;

public:
    Game();

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, double width, double height);

    void OnUpdate(double elapsed, long time);

    void Add(std::shared_ptr<Item> item);

    void Load(const wxString &filename);

    /**
     * Get the random number generator
     * @return Pointer to the random number generator
     */
    std::mt19937 &GetRandom() { return mRandom; }
    void Save(const wxString &filename);
};

#endif //ARES_GAMELIB_GAME_H
