/**
 * @file Background.cpp
 * @author jadec
 */

#include "Background.h"

/**
 * Constructor
 * @param game The game this background is a member of
 * @param dec The declaration node containing all the information to create a basic background
 * @param item The item node containing the location information for this specific background
 */
Background::Background(Game *game, wxXmlNode * dec, wxXmlNode* item) : Item(game, dec, item)
{

}
