/**
 * @file DeclarationInteract.cpp
 * @author jadec
 */

#include "pch.h"
#include "DeclarationInteract.h"

DeclarationInteract::DeclarationInteract(Game *game) : DeclarationNumber(game) {}

shared_ptr<Item> DeclarationInteract::Create(wxXmlNode *node)
{
    return nullptr;
}
