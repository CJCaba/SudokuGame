/**
 * @file InteractNumber.h
 * @author Jaden Cabansag
 *
 * Derived Class for Numbers that can be eaten by Sparty
 */

#ifndef ARES_GAMELIB_INTERACTNUMBER_H
#define ARES_GAMELIB_INTERACTNUMBER_H

#include "Number.h"

/**
 * Base class for Interactable Number
 */
class InteractNumber : public Number
{
protected:
private:
    /// Flag representing whether this number resides in a X-Ray
    bool mXRayFlag = false;

public:
    InteractNumber(Game *game, wxXmlNode * dec, wxXmlNode* item);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(Visitor* visitor) override { visitor->VisitInteract(this); }

    /**
     * Setter for X-Ray flag
     * @param b boolean to set
     */
    void SetXRayFlag(bool b) { mXRayFlag = b; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
};

#endif //ARES_GAMELIB_INTERACTNUMBER_H
