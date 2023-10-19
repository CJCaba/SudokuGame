/**
 * @file DeclarationNumber.cpp
 * @author jadec
 */

#include "pch.h"
#include "DeclarationNumber.h"
#include "Game.h"

DeclarationNumber::DeclarationNumber(Game *game) : Declaration(game)
{

}

void DeclarationNumber::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);
    node->GetAttribute("value", "0").ToInt(&mValue);
}
