/**
 * @file DeclarationNumber.h
 * @author jadec
 *
 *
 */

#ifndef ARES_GAMELIB_DECLARATIONNUMBER_H
#define ARES_GAMELIB_DECLARATIONNUMBER_H

#include "Declaration.h"

class DeclarationNumber : public Declaration
{
private:
    int mValue;
public:
    DeclarationNumber(Game *game);

    /// Default constructor (disabled)
    DeclarationNumber() = delete;

    /// Copy constructor (disabled)
    DeclarationNumber(const DeclarationNumber &) = delete;

    /// Assignment operator
    void operator=(const DeclarationNumber &) = delete;

    void SetValue(int i) { mValue = i; }
    int GetValue() const { return mValue; }

};

#endif //ARES_GAMELIB_DECLARATIONNUMBER_H
