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
    /// Default constructor (disabled)
    InteractNumber() = delete;
    
    /// Copy constructor (disabled)
    InteractNumber(const InteractNumber &) = delete;
    
    /// Assignment operator
    void operator=(const InteractNumber &) = delete;
    
    
};

#endif //ARES_GAMELIB_INTERACTNUMBER_H
