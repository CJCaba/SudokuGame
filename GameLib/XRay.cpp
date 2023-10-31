/**
 * @file XRay.cpp
 * @author linja
 */

#include "pch.h"
#include "XRay.h"

XRay::XRay(Game *game, wxXmlNode * dec, wxXmlNode* item) : Item(game, dec, item)
{
}

void XRay::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Item::Draw(graphics);
}