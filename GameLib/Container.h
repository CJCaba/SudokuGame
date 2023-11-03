/**
 * @file Container.h
 * @author Gerald Hoskins
 * @author Jaden Cabansag
 * This file implements `Container`
 */

#ifndef ARES_GAMELIB_CONTAINER_H
#define ARES_GAMELIB_CONTAINER_H

#include <wx/graphics.h>
#include "Item.h"

/**
 * This class implements containers
 */
class Container : public Item
{
protected:

private:
    /// The game this container is a part of
    Game *mGame;

    /// Items within the container
    std::vector<std::shared_ptr<Item>> mItems;

    /// The back image of the container
    std::unique_ptr<wxImage> mBackImage;

    /// The back bitmap of the container
    wxGraphicsBitmap mBackBitmap;

    /// The front image of the container
    std::unique_ptr<wxImage> mFrontImage;

    /// The front bitmap of the container
    wxGraphicsBitmap mFrontBitmap;

    double mX = 0;  ///< X position of the item
    double mY = 0;  ///< Y position of the item

public:

    Container(Game *game, wxXmlNode* dec, wxXmlNode* item);

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
     * Set the container location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y) { mX = x; mY = y; }

    /**
       * Get Width of an image in pixels
       * @return double representing width of the item
       */
    double GetWidth() { return mBackImage->GetWidth(); }

    /**
      * Get height of an image in pixels
      * @return double representing the height of the item
      */
    double GetHeight() { return mBackImage->GetHeight(); }

    /**
    * Adds an item to the container
    * @param item to add
    */
    void Add(const std::shared_ptr<Item>& item);

    /**
    * Moves contained items to random locations
    * across the screen, then clears the container.
    */
    void Release();

    /**
    * Draw the container.
    * @param graphics Graphics context to draw the container on.
    */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
      * Check whether the point is within the bounds of this item
      * @param point point to check
      * @return boolean representing yes/no
      */
    virtual bool HitTest(double x, double y) const override
    {
        return (x > mX &&
            x < (mX + mFrontImage->GetWidth()) &&
            y > mY && y < (mY + mFrontImage->GetHeight()));
    }

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(Visitor* visitor) override { visitor->VisitContainer(this); }
};

#endif //ARES_GAMELIB_CONTAINER_H
