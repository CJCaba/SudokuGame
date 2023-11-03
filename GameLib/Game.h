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
#include <wx/sound.h>

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

    /// Pointer to the Sparty Item
    std::shared_ptr<Sparty> mSparty = nullptr;

    /// Pointer to the XRay Item
    std::shared_ptr<XRay> mXRay = nullptr;

    /// Pointer to the Spotlight Item
    std::shared_ptr<Spotlight> mSpotlight = nullptr;

    /// Location of the Spotlight Item
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

    /// The Pixel Width of the Game
    double mPixelWidth = 0;

    /// The Pixel Height of the Game
    double mPixelHeight = 0;

    /// Random number generator
    std::mt19937 mRandom;

    /// Object containing the runtime of the game
    std::shared_ptr<Clock> mClock;

    /// Map of Declarations, with IDs as keys
    std::map<std::string, wxXmlNode*> mDeclarations;

    /// Map of Image pointers to IDs
    std::map<std::string, std::shared_ptr<wxImage>> mImages;

    /// 2D Map of the Virtual Board State
    int mSolution[9][9] = {0};

    /// Bool Value to determine whether game is starting up or not
    bool mStartUp = true;

    /// Int value for level playing currently
    int mCurrentLevel;

    /// Tile Width of the Game
    int mTileWidth;

    /// Tile Height of the Game
    int mTileHeight;

    /// Width of the game
    double mGameWidth = 0;

    /// Height of the game
    double mGameHeight = 0;

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

    bool WithinWidth(double x);

    bool WithinHeight(double y);

    /**
     * Get the random number generator
     * @return Pointer to the random number generator
     */
    std::mt19937 &GetRandom() { return mRandom; }

    /**
     * Return the Pixel Width
     * @return mPixelWidth
     */
    double GetWidth() const { return mPixelWidth; }

    /**
     * Return the Pixel Width
     * @return mPixelHeight
     */
    double GetHeight() const { return mPixelHeight; }

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

    /**
     * Get the Tile Width
     * @return mTileWidth
     */
    int GetTileWidth() const { return mTileWidth; }

    /**
     * Get the Tile Height
     * @return mTileHeight
     */
    int GetTileHeight() const { return mTileHeight; }

    void XmlDeclare(wxXmlNode *node);

    void XmlItem(wxXmlNode *node);

    void SetLevel(std::wstring filename);

    void OnKeyDown(wxKeyEvent &event);

    void TutorialPrompt(std::shared_ptr<wxGraphicsContext> graphics);

    std::shared_ptr<wxImage> GetImage(const std::string& id);

    void Accept(Visitor* visitor);

    /**
     * Getter for Clock instance
     * @return the clock
     */
    std::shared_ptr<Clock> GetClock() { return mClock; };

    void UpdateBoard();

    void CheckSolution();

    void Solve();

    void DrawEndScreen(std::shared_ptr<wxGraphicsContext> graphics, wxString EndText);

    std::wstring DetermineStartupText();
};

#endif //ARES_GAMELIB_GAME_H
