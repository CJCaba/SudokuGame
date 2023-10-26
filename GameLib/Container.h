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
    /// Default constructor (disabled)
    Container() = delete;

    /// Copy constructor (disabled)
    Container(const Container &) = delete;

    /// Assignment operator
    void operator=(const Container &) = delete;

    virtual ~Container();

    Container(Game *game, const std::wstring &backImageFilename, const std::wstring &frontImageFilename);

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

    void Add(const std::shared_ptr<Item>& item);
    void Release();

    /**
     * Is the item in the container?
     * @param item The item in question.
     * @return bool representing yes/no.
     */
    bool Contains(const std::shared_ptr<Item>& item) { return std::find(mItems.begin(), mItems.end(), item) != mItems.end(); };

    void Draw(const std::shared_ptr<wxGraphicsContext>& graphics);
};

#endif //ARES_GAMELIB_CONTAINER_H
