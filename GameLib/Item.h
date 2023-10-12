/**
 * @file Item.h
 * @author Tyler Przybylo
 *
 * Base class for items in the game
 */

#ifndef ARES_GAMELIB_ITEM_H
#define ARES_GAMELIB_ITEM_H

#include <memory>

// Uncomment this once Game class is made
// class Game;

/**
 * Base class for items in the game
 */
class Item
{
private:
    /// The game that the item is currently in
    // Uncomment this once Game class is made
    // Game *mGame;

    double mX = 0; ///< X position of the item
    double mY = 0; ///< Y position of the item

    /// The image for this tile
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap for this tile
    std::unique_ptr<wxBitmap> mItemBitmap;

    /// The file for this item
    std::wstring mFile;
public:
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;
};

#endif //ARES_GAMELIB_ITEM_H
