/**
 * @file Spotlight.cpp
 * @author Tyler Przybylo
 */

#include "pch.h"

#include "Spotlight.h"

/**
 * Constructor
 * @param game The game this spotlight is a member of
 * @param dec The declaration node containing all the information to create a basic spotlight
 * @param item The item node containing the location information for this specific spotlight
 */
Spotlight::Spotlight(Game *game, wxXmlNode * dec, wxXmlNode* item) : Item(game, dec, item)
{

}


