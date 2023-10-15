/**
 * @file GivenNumber.h
 * @author Jaden Cabansag
 *
 * Base Class for a number
 */

#ifndef ARES_GAMELIB_GIVENNUMBER_H
#define ARES_GAMELIB_GIVENNUMBER_H

#include "Item.h"

/**
 * Base class for a Given Number
 */
class GivenNumber : public Item
{
protected:
    GivenNumber(Game *game, const std::wstring &filename);
private:
    int value;
public:
    /// Default constructor (disabled)
    GivenNumber() = delete;
    
    /// Copy constructor (disabled)
    GivenNumber(const GivenNumber &) = delete;
    
    /// Assignment operator
    void operator=(const GivenNumber &) = delete;

    /**
     * Return value of this number
     * @return value
     */
    int GetValue() { return value; }
    
};

#endif //ARES_GAMELIB_GIVENNUMBER_H
