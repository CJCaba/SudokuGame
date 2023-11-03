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
#include "Visitor.h"

/**
 * Base class for Items in the game
 */
class Item
{
private:
    /// The ID of this item given by its declaration
    std::string mID;

    double mX = 0; ///< X position of the item
    double mY = 0; ///< Y position of the item

    /// The bitmap for this tile
    wxGraphicsBitmap mItemBitmap;

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
    Item(Game *game, wxXmlNode *dec, wxXmlNode *item);

    /**
     * The X location of the item
     * @return X location in pixels
     */
    virtual double GetX() const { return mX; }

     /**
      * The Y location of the item
      * @return Y location in pixels
      */
     virtual double GetY() const { return mY; }


     /**
      * The bitmap for this Item
      * @return bitmap of item image
      */
     virtual wxGraphicsBitmap GetBitMap() {return mItemBitmap;}

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
     double GetWidth() const { return mGame->GetImage(mID)->GetWidth(); }

     /**
       * Get height of an image in pixels
       * @return double representing the height of the item
       */
     double GetHeight() const { return mGame->GetImage(mID)->GetHeight(); }

     virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

     /**
      * Get the Game class that this item is a part of
      * @return Pointer to the Game class
      */
     Game* GetGame() { return mGame; }

     bool OnBoard(wxPoint point);

     /**
      * Check whether the point is within bounds of this item
      * @param x coordinate as double
      * @param y coordinate as double
      * @return boolean representing true/false
      */
     virtual bool HitTest(double x, double y) const
     {
         return (x >= mX && x < (mX + GetWidth()) && y >= mY && y < (mY + GetHeight()));
     }

     /**
      * Abstract function for items to accept visitors
      * @param visitor The visitor going through the items
      */
     virtual void Accept(Visitor* visitor) = 0;
};

#endif //ARES_GAMELIB_ITEM_H
