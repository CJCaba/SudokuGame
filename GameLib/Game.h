/**
 * @file Game.h
 * @author Daniel Flanagan
 *
 * Class that implements the game
 */

#ifndef ARES_GAMELIB_GAME_H
#define ARES_GAMELIB_GAME_H

#include <vector>

#include "Item.h"

/**
 * Implements a game class with necessary items
 */
class Game
{
private:
    /// Collection of items within the game
    std::vector<std::shared_ptr<Item>> mItems;

    std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use

public:
    void Add(std::shared_ptr<Item> item);


};

#endif //ARES_GAMELIB_GAME_H
