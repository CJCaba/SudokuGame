/**
 * @file Game.h
 * @authors Daniel Flanagan and Tyler Przybylo
 *
 * Class that implements the game
 */

#ifndef ARES_GAMELIB_GAME_H
#define ARES_GAMELIB_GAME_H

#include <vector>

#include "Item.h"
#include <wx/graphics.h>

/**
 * Implements a game class with necessary items
 */
class Game
{
private:
    /// Collection of items within the game
    std::vector<std::shared_ptr<Item>> mItems;

    std::shared_ptr<wxImage> mBackgroundImage;  ///< Background image to use

    wxGraphicsBitmap mBackgroundBitmap; ///< The background bitmap

    /// The current scale of our game made in comparison to our window
    double mScale;

    /// The amount to shift the graphics object in the x direction
    double mXOffset;

    /// The amount to shift the graphics object in the y direction
    double mYOffset;

public:
    Game();

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    void Add(std::shared_ptr<Item> item);


};

#endif //ARES_GAMELIB_GAME_H
