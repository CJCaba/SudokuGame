/**
 * @file Declaration.h
 * @author jadec
 *
 *
 */

#ifndef ARES_GAMELIB_DECLARATION_H
#define ARES_GAMELIB_DECLARATION_H

class Game;
using namespace std;

class Declaration
{
private:
    /// The ID for each specific Item
    string mID;

    /// The width of the Item Image
    double width;

    /// The height of the Item Image
    double height;

    /// The Image Filename
    wstring imageFile;

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
