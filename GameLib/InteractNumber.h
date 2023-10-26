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

public:
    InteractNumber(Game *game, wxXmlNode * dec);


};

#endif //ARES_GAMELIB_INTERACTNUMBER_H
