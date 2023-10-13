/**
 * @file Game.cpp
 * @author Daniel Flanagan
 */

#include "pch.h"
#include "Game.h"

using namespace std;

/**
 * Add an item to the game
 * @param item New item to add
 */
void Game::Add(std::shared_ptr<Item> item)
{
    // Code for setting an items location can go here

    mItems.push_back(item);
}

