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
private:

public:
    InteractNumber(Game *game, const std::wstring &filename);


};

#endif //ARES_GAMELIB_INTERACTNUMBER_H
