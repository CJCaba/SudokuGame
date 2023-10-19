/**
 * @file XRay.cpp
 * @author linja
 */

#include "pch.h"
#include "XRay.h"

XRay::XRay(Game *game, const std::wstring &filename) : Item(game, filename)
{
}

void XRay::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    SetLocation(10, 575);
    Item::Draw(graphics);
}