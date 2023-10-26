/**
 * @file DeclarationInteract.h
 * @author jadec
 *
 *
 */

#ifndef ARES_GAMELIB_DECLARATIONINTERACT_H
#define ARES_GAMELIB_DECLARATIONINTERACT_H

#include "DeclarationNumber.h"
#include "InteractNumber.h"

class DeclarationInteract : public DeclarationNumber
{
private:

public:
    DeclarationInteract(Game *game);

    shared_ptr<Item> Create(wxXmlNode *node) override;
};

#endif //ARES_GAMELIB_DECLARATIONINTERACT_H
