/**
 * @file Background.h
 * @author jadec
 *
 * Class for all background items in the Xml file
 */

#ifndef ARES_GAMELIB_BACKGROUND_H
#define ARES_GAMELIB_BACKGROUND_H
#include "Item.h"

/**
 * Base class for Background
 */
class Background : public Item
{
private:

public:
    Background(Game *game, wxXmlNode * dec, wxXmlNode* item);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(Visitor* visitor) override { visitor->VisitBackground(this); }
};

#endif //ARES_GAMELIB_BACKGROUND_H
