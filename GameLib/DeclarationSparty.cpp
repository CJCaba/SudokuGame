/**
 * @file DeclarationSparty.cpp
 * @author jadec
 */

#include "DeclarationSparty.h"

DeclarationSparty::DeclarationSparty(Game *game) : Declaration(game) {}


void DeclarationSparty::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);
    node->GetAttribute("front", "0").ToDouble(&mFront);
    node->GetAttribute("head-pivot-angle", "0").ToDouble(&mHeadPivotAngle);
    node->GetAttribute("head-pivot-x", "0").ToDouble(&mHeadPivotX);
    node->GetAttribute("head-pivot-y", "0").ToDouble(&mHeadPivotY);
    mImage1 = node->GetAttribute("image1").ToStdWstring();
    mImage2 = node->GetAttribute("image2").ToStdWstring();
    node->GetAttribute("mouth-pivot-angle", "0").ToDouble(&mMouthPivotAngle);
    node->GetAttribute("mouth=pivot-x", "0").ToDouble(&mMouthPivotX);
    node->GetAttribute("mouth-pivot-y", "0").ToDouble(&mMouthPivotY);
    node->GetAttribute("target-x", "0").ToDouble(&mTargetX);
    node->GetAttribute("target-y", "0").ToDouble(&mTargetY);
}
