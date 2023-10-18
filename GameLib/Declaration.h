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

class Declaration
{
private:
    /// The ID for each specific Item
    string mID;

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

    /**
     * Get the ID
     */
     string GetID() { return mID; }
};

#endif //ARES_GAMELIB_DECLARATION_H
