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
    double mFront;

    double mHeadPivotAngle;

    double mHeadPivotX;

    double mHeadPivotY;

    double mMouthPivotAngle;

    double mMouthPivotX;

    double mMouthPivotY;

    double mTargetX;

    double mTargetY;

    wstring mImage1;
    wstring mImage2;

public:
    DeclarationSparty(Game *game);

    void XmlLoad(wxXmlNode *node) override;
};

#endif //ARES_GAMELIB_DECLARATIONSPARTY_H
