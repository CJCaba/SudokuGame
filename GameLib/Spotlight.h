/**
 * @file Spotlight.h
 * @author Tyler Przybylo
 *
 * Class for the spotlight on level 3
 */

#ifndef ARES_GAMELIB_SPOTLIGHT_H
#define ARES_GAMELIB_SPOTLIGHT_H

#include "Item.h"

/**
 * Base Class for the spotlight
 */
class Spotlight : public Item
{
private:

public:
    /// Constructor
    Spotlight(Game *game, wxXmlNode * dec, wxXmlNode* item);

    /**
      * Draw this item
      * @param gc Device context to draw on
      */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(Visitor* visitor) override { visitor->VisitSpotlight(this); }
};

#endif //ARES_GAMELIB_SPOTLIGHT_H
