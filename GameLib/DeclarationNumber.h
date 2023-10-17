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
    int value;
public:
    DeclarationNumber(double width, double height, const wstring &fileName, int value);

};

#endif //ARES_GAMELIB_DECLARATIONNUMBER_H
