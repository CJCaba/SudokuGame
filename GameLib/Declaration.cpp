/**
 * @file Declaration.cpp
 * @author jadec
 */

#include "pch.h"
#include "Declaration.h"

Declaration::Declaration(Game *game) : mGame(game)
{

}

void Declaration::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute("width", "0").ToDouble(&mWidth);
    node->GetAttribute("height", "0").ToDouble(&mHeight);
    mImageFile = node->GetAttribute("image", "0").ToStdWstring();
}

shared_ptr<Item> Declaration::Create(wxXmlNode *node)
{
    return shared_ptr<Item>();
}
