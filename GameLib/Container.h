/**
 * @file Container.h
 * @author Gerald Hoskins
 *
 * This file implements `Container`
 */

#ifndef ARES_GAMELIB_CONTAINER_H
#define ARES_GAMELIB_CONTAINER_H

#include <wx/graphics.h>
#include "Item.h"

/**
 * This class implements containers
 */
class Container
{
private:
    /// Items within the container
    std::vector<std::shared_ptr<Item>> mItems;

    /// The bottom image of the container
    std::unique_ptr<wxImage> mBottomImage;

    /// The bottom bitmap of the container
    wxGraphicsBitmap mBottomBitmap;

    /// The top image of the container
    std::unique_ptr<wxImage> mTopImage;

    /// The top bitmap of the container
    wxGraphicsBitmap mTopBitmap;

    double mX = 0;  ///< X position of the item
    double mY = 0;  ///< Y position of the item

public:
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
       * Get Width of an image in pixels
       * @return double representing width of the item
       */
    double GetWidth() { return mBottomImage->GetWidth(); }

    /**
      * Get height of an image in pixels
      * @return double representing the height of the item
      */
    double GetHeight() { return mBottomImage->GetHeight(); }

    void add(std::shared_ptr<Item> item);
    void release();

    /**
     * Is the item in the container?
     * @return bool representing yes/no.
     */
    bool contains(std::shared_ptr<Item> item) { return std::find(mItems.begin(), mItems.end(), item) != mItems.end(); };

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
};

#endif //ARES_GAMELIB_CONTAINER_H
