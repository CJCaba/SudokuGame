/**
 * @file Number.h
 * @author Jaden Cabansag
 *
 * Base Class for a number
 */

#ifndef ARES_GAMELIB_NUMBER_H
#define ARES_GAMELIB_NUMBER_H

#include "Item.h"

/**
 * Base class for a Number
 * This applies to all of the numbers,
 * but not sparty or the containers
 */
class Number : public Item
{
protected:
    Number(Game *game, const std::wstring &filename);
private:

public:
    /// Default constructor (disabled)
    Number() = delete;
    
    /// Copy constructor (disabled)
    Number(const Number &) = delete;
    
    /// Assignment operator
    void operator=(const Number &) = delete;
    
    
};

#endif //ARES_GAMELIB_NUMBER_H
