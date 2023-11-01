/**
 * @file Game.h
 * @authors Daniel Flanagan, Tyler Przybylo, and Jason Lin
 *
 * Class that implements the game
 */

#ifndef ARES_GAMELIB_GAME_H
#define ARES_GAMELIB_GAME_H

#include <random>
#include <vector>
#include <memory>
#include <map>
#include <wx/graphics.h>

class Declaration;
class Clock;
class Item;
class Container;
class Sparty;
class XRay;
class Solution;
class Visitor;

/**
 * Implements a game class with necessary items
 */
class Game
{
private:
    /// Collection of items within the game
    std::vector<std::shared_ptr<Item>> mItems;

    /// Collection of containers within the game
    std::vector<std::shared_ptr<Container>> mContainers;

    std::shared_ptr<Sparty> mSparty = nullptr;

    std::shared_ptr<XRay> mXRay = nullptr;

    /// Solution to the game
    std::shared_ptr<Solution> mGameSolution;

    std::shared_ptr<wxImage> mBackgroundImage;  ///< Background image to use

    wxGraphicsBitmap mBackgroundBitmap; ///< The background bitmap

    /// The current scale of our game made in comparison to our window
    double mScale = 1;

    /// The amount to shift the graphics object in the x direction
    double mXOffset = 0;

    /// The amount to shift the graphics object in the y direction
    double mYOffset = 0;

    double mPixelWidth = 0;

    double mPixelHeight = 0;

    /// Random number generator
    std::mt19937 mRandom;

    /// Object containing the runtime of the game
    std::shared_ptr<Clock> mClock;

    /// Map of Declarations, with IDs as keys
    std::map<std::string, wxXmlNode*> mDeclarations;

    /// Map of Image pointers to IDs
    std::map<std::string, std::shared_ptr<wxImage>> mImages;

    int mSolution[9][9] = {0};
//        {{9,9,9,9,9,9,9,9,9},
//                           {9,9,9,9,9,9,9,9,9},
//                           {9,9,9,9,9,9,9,9,9},
//                           {9,9,9,9,9,9,9,9,9},
//                           {9,9,9,9,9,9,9,9,9},
//                           {9,9,9,9,9,9,9,9,9},
//                           {9,9,9,9,9,9,9,9,9},
//                           {9,9,9,9,9,9,9,9,9},
//                           {9,9,9,9,9,9,9,9,9}};

    bool mStartUp = true;

    std::wstring mCurrentLevel;

    int mTileWidth;
    int mTileHeight;

public:
    Game();

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, double width, double height);

    void OnUpdate(double elapsed);

    void OnLeftDown(wxMouseEvent &event);

    void AddItem(std::shared_ptr<Item> item);

    void Load(const wxString &filename);

    void Clear();

    /**
     * Get the random number generator
     * @return Pointer to the random number generator
     */
    std::mt19937 &GetRandom() { return mRandom; }

    void Save(const wxString &filename);

    bool WithinWidth(double x);

    bool WithinHeight(double y);

    double GetWidth() const { return mPixelWidth; }

    double GetHeight() const { return mPixelHeight; }

    std::wstring DetermineStartupText();


    /**
     * Getter for items.
     * @return Pointers to items stored in a vector.
     */
    std::vector<std::shared_ptr<Item>> GetItems() const { return mItems; }

    /**
     * Getter for Map of Declarations
     * @return
     */
    std::map<std::string, wxXmlNode*> GetDec() const { return mDeclarations; }

    int GetTileWidth() const { return mTileWidth; }
    int GetTileHeight() const { return mTileHeight; }

    void XmlDeclare(wxXmlNode *node);
    void XmlItem(wxXmlNode *node);
    void SetLevel(std::wstring filename);
    void OnKeyDown(wxKeyEvent &event);
    void TutorialPrompt(std::shared_ptr<wxGraphicsContext> graphics);

    std::shared_ptr<wxImage> GetImage(const std::string& id);

    void Accept(Visitor* visitor);

    void UpdateBoard();
};

#endif //ARES_GAMELIB_GAME_H
