/**
 * @file DeclarationSparty.h
 * @author jadec
 *
 *
 */

#ifndef ARES_GAMELIB_DECLARATIONSPARTY_H
#define ARES_GAMELIB_DECLARATIONSPARTY_H

#include "Declaration.h"

class DeclarationSparty : public Declaration
{
private:
    int mFront;

    double mHeadPivotAngle;

    double mHeadPivotX;

    double mHeadPivotY;

    double mMouthPivotAngle;

    double mMouthPivotX;

    double mMouthPivotY;

    double mTargetX;

    double mTargetY;
public:
    DeclarationSparty(Game *game);
};

#endif //ARES_GAMELIB_DECLARATIONSPARTY_H
