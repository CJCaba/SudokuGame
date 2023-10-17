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
    int value;

public:

    /**
    * Return value of this number
    * @return value
    */
    int GetValue() { return value; }
};

#endif //ARES_GAMELIB_INTERACTNUMBER_H
