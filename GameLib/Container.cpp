/**
 * @file Container.cpp
 * @author Gerald Hoskins
 */

#include "pch.h"

#include <random>

#include "Container.h"

/**
 * Adds an item to the container
 * @param item to add
 */
void Container::add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Pops the item out of the container. This will return nullptr if not found.
 * @param item Item to
 * @return
 */
void Container::release()
{
//    for (std::shared_ptr<Item> item : mItems)
//    {
//        std::uniform_real_distribution<> distributionX(minX, maxX);
//        std::uniform_real_distribution<> distributionY(minY, maxY);
//        X = distributionX(Item::GetGame()->GetRandom());
//        Y = distributionY(Item::GetGame()->GetRandom());
//        item->SetLocation(X, Y);
//    }
}