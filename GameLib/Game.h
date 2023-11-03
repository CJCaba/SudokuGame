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
class ImFullErrorMessage;
class Spotlight;

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

    /// Collection of error messages within the game
    std::vector<std::shared_ptr<ImFullErrorMessage>> mErrorMessages;

    std::shared_ptr<Sparty> mSparty = nullptr;

    std::shared_ptr<XRay> mXRay = nullptr;

    std::shared_ptr<Spotlight> mSpotlight = nullptr;

    wxPoint mSpotlightLocation;

    /// Solution to the game
    std::shared_ptr<Solution> mGameSolution = nullptr;

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

    bool mStartUp = true;

    int mCurrentLevel;

    int mTileWidth;
    int mTileHeight;

    /// True if level is lost
    bool mLevelLost = false;

    /// True if level is won
    bool mLevelWon = false;

    /// Records time of level victory
    int mFinishTime = -1;

public:
    Game();

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, double width, double height);

    void OnUpdate(double elapsed);

    void OnLeftDown(wxMouseEvent &event);

    void OnMouseMove(wxMouseEvent &event);

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

    /**
     * Game accepts visitor to view mItems list
     * @param visitor
     */
    void Accept(Visitor* visitor);

    void UpdateBoard();
    void CheckSolution();

    void Solve();
    void DrawEndScreen(std::shared_ptr<wxGraphicsContext> graphics, wxString EndText);
};

#endif //ARES_GAMELIB_GAME_H
