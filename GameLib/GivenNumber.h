/**
 * @file GivenNumber.h
 * @author Jaden Cabansag
 *
 * Derived class for numbers already set in play area
 */

#ifndef ARES_GAMELIB_GIVENNUMBER_H
#define ARES_GAMELIB_GIVENNUMBER_H

#include "Number.h"

/**
 * Base Class for Given Number
 */
class GivenNumber : public Number
{
private:

public:
    /// Default constructor (disabled)
    GivenNumber() = delete;
    
    /// Copy constructor (disabled)
    GivenNumber(const GivenNumber &) = delete;
    
    /// Assignment operator
    void operator=(const GivenNumber &) = delete;
    
    
};

#endif //ARES_GAMELIB_GIVENNUMBER_H
