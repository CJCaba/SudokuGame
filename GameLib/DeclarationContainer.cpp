/**
 * @file DeclarationContainer.cpp
 * @author Tyler Przybylo
 */

#include "pch.h"

#include "DeclarationContainer.h"

DeclarationContainer::DeclarationContainer(Game *game) : Declaration(game) {}

void DeclarationContainer::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);
    mFront = node->GetAttribute("front", "0").ToStdWstring();
}