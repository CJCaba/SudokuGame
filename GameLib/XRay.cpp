/**
 * @file XRay.cpp
 * @author linja
 */

#include "pch.h"
#include "XRay.h"

// Hard Coded X-Ray Attributes
const double x = 0.6042;
const double y = 14.0;
const double tileSize = 48;
const double tileOffset = 96;

XRay::XRay(Game *game, wxXmlNode * dec, wxXmlNode* item) : Item(game, dec, item)
{
}

void XRay::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    SetLocation(x * tileSize, y * tileSize - tileOffset);
    Item::Draw(graphics);
}