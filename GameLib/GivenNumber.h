/**
 * @file GivenNumber.h
 * @author Jaden Cabansag
 *
 * Base Class for a number
 */

#ifndef ARES_GAMELIB_GIVENNUMBER_H
#define ARES_GAMELIB_GIVENNUMBER_H

#include "Number.h"

/**
 * Base class for a Given Number
 */
class GivenNumber : public Number
{
protected:
private:
public:
    GivenNumber(Game *game, wxXmlNode * dec, wxXmlNode* item);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(Visitor* visitor) override { visitor->VisitGiven(this); }
};

#endif //ARES_GAMELIB_GIVENNUMBER_H
