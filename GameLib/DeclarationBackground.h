/**
 * @file DeclarationBackground.h
 * @author jadec
 *
 *
 */

#ifndef ARES_GAMELIB_DECLARATIONBACKGROUND_H
#define ARES_GAMELIB_DECLARATIONBACKGROUND_H
#include "Declaration.h"
class DeclarationBackground : public Declaration
{
private:

public:
    DeclarationBackground(Game *game);

    void XmlLoad(wxXmlNode *node) override { Declaration::XmlLoad(node); };
};

#endif //ARES_GAMELIB_DECLARATIONBACKGROUND_H
