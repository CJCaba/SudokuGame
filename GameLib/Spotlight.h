/**
 * @file Spotlight.h
 * @author Tyler Przybylo
 *
 * Class for the spotlight on level 3
 */

#ifndef ARES_GAMELIB_SPOTLIGHT_H
#define ARES_GAMELIB_SPOTLIGHT_H

#include "Item.h"

class Spotlight : public Item
{
private:

public:
    /// Constructor
    Spotlight(Game *game, wxXmlNode * dec, wxXmlNode* item);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(Visitor* visitor) override { visitor->VisitSpotlight(this); }
};

#endif //ARES_GAMELIB_SPOTLIGHT_H
