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
//    GivenNumber(Game *game, const std::wstring &filename);
private:
    int value;
public:

    /**
     * Return value of this number
     * @return value
     */
    int GetValue() { return value; }
    
};

#endif //ARES_GAMELIB_GIVENNUMBER_H
