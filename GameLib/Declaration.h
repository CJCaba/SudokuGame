/**
 * @file Declaration.h
 * @author jadec
 *
 *
 */

#ifndef ARES_GAMELIB_DECLARATION_H
#define ARES_GAMELIB_DECLARATION_H


using namespace std;

class Game;
#include "Item.h"

class Declaration
{
private:
    /// The width of the Item Image
    double mWidth;

    /// The height of the Item Image
    double mHeight;

    /// The Image Filename
    wstring mImageFile;

    Game *mGame;

protected:
    Declaration(Game *game);

public:
    /// Default constructor (disabled)
    Declaration() = delete;

    /// Copy constructor (disabled)
    Declaration(const Declaration &) = delete;

    /// Assignment operator
    void operator=(const Declaration &) = delete;

    void SetSize(double width, double height) { mWidth = width; mHeight = height; }

    void SetImage(wstring fileName) { mImageFile = fileName; }

    virtual void XmlLoad(wxXmlNode *node);

    double GetWidth() const { return mWidth; }
    double GetHeight() const { return mHeight; }
    wstring GetImage() const { return mImageFile; }
    Game * GetGame() const { return mGame; }

    virtual shared_ptr<Item> Create(wxXmlNode *node);
};

#endif //ARES_GAMELIB_DECLARATION_H
