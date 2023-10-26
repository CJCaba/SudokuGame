/**
 * @file DeclarationContainer.h
 * @author Tyler Przybylo
 *
 * Container Declaration
 */

#ifndef ARES_GAMELIB_DECLARATIONCONTAINER_H
#define ARES_GAMELIB_DECLARATIONCONTAINER_H

#include "Declaration.h"

/**
 * Container Declaration
 */
class DeclarationContainer : public Declaration
{
private:
    /// Front of container image (back is already got from upcall to Declaration)
    wstring mFront;
public:
    DeclarationContainer(Game *game);

    void XmlLoad(wxXmlNode *node) override;

    wstring GetFront() const { return mFront; }
};

#endif //ARES_GAMELIB_DECLARATIONCONTAINER_H
