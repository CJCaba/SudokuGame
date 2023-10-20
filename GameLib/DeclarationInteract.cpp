/**
 * @file DeclarationInteract.cpp
 * @author jadec
 */

#include "pch.h"
#include "DeclarationInteract.h"

DeclarationInteract::DeclarationInteract(Game *game) : DeclarationNumber(game) {}

shared_ptr<InteractNumber> DeclarationInteract::Declare()
{
    shared_ptr<InteractNumber> inNum = make_shared<InteractNumber>(GetGame(), GetImage());
    inNum->SetValue(GetValue());
    return inNum;
}
