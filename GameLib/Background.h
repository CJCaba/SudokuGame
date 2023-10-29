/**
 * @file Background.h
 * @author jadec
 *
 *
 */

#ifndef ARES_GAMELIB_BACKGROUND_H
#define ARES_GAMELIB_BACKGROUND_H
#include "Item.h"
class Background : public Item
{
private:

public:
    Background(Game *game, wxXmlNode * dec, wxXmlNode* item);
};

#endif //ARES_GAMELIB_BACKGROUND_H
