/**
 * @file Item.h
 * @author Tyler Przybylo
 * @author Jaden Cabansag
 *
 * Base class for items in the game
 */

#ifndef ARES_GAMELIB_ITEM_H
#define ARES_GAMELIB_ITEM_H

#include <memory>
#include <wx/graphics.h>

#include "Game.h"

/**
 * Base class for Numbers in the game
 */
class Item
{
private:
    double mX = 0; ///< X position of the item
    double mY = 0; ///< Y position of the item

    /// The image for this tile
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap for this tile
    wxGraphicsBitmap mItemBitmap;

    /// The file for this item
    std::wstring mFile;

    /// The game this item is contained in
    Game *mGame;

public:
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;

    /// Destructor
    virtual ~Item();

    /// Constructor
    Item(Game *game, const std::wstring &filename);

    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

     /**
      * The Y location of the item
      * @return Y location in pixels
      */
     double GetY() const { return mY; }

     /**
      * Set the item location
      * @param x X location in pixels
      * @param y Y location in pixels
      */
     virtual void SetLocation(double x, double y) { mX = x; mY = y; }

     /**
       * Get Width of an image in pixels
       * @return double representing width of the item
       */
     double GetWidth() { return mItemImage->GetWidth(); }

     /**
       * Get height of an image in pixels
       * @return double representing the height of the item
       */
     double GetHeight() { return mItemImage->GetHeight(); }

     /**
       * Draw this item
       * @param gc Device context to draw on
       */
     virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

     /**
      * Get the Game class that this item is a part of
      * @return Pointer to the Game class
      */
     Game* GetGame() { return mGame; }
};

#endif //ARES_GAMELIB_ITEM_H
