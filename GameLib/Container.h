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

    /// The image of the container
    std::unique_ptr<wxBitmap> mImage;

    double mX = 0;  ///< X position of the item
    double mY = 0;  ///< Y position of the item

public:
    void add(std::shared_ptr<Item> item);
    void release();
};

#endif //ARES_GAMELIB_CONTAINER_H
