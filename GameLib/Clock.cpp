/**
 * @file Clock.cpp
 * @author Jason Lin
 */

#include "pch.h"
#include "Clock.h"
#include "Game.h"

#include <iostream>

/// Size of the scoreboard text in virtual pixels
const int ScoreboardTextSize = 64;

/// Top left corner of the scoreboard in virtual pixels
const wxPoint ScoreboardTopLeft(10, 10);

/**
 * Constructor
 * @param game The game this clock is a member of
 */
Clock::Clock(Game *game) : mGame(game)
{
}

/**
 * Destructor
 */
Clock::~Clock()
{
}

/**
 * Set the analog time based on current stopwatch elapse
 * @param time time since stopwatch started
 */
void Clock::SetTime(long time)
{
    // Divides the number of seconds
    mSeconds = time / 1000;
    mMinutes = mSeconds / 60;

    if(mSeconds >= 60)
    {
        mSeconds -= mMinutes * 60;
    }
}

/**
 * Increment the clock counter
 * @param elapsed The amount of time to add to mSeconds
 */
void Clock::AddTime(double elapsed)
{
    mSeconds += elapsed;

    if(mSeconds >= 60)
    {
        mSeconds -= 60;
        mMinutes += 1;
    }
}

/**
 * Converts analog minutes to a string
 * @return minutes as type string
 */
std::string Clock::GetMinutes()
{
    std::string mins = std::to_string(int(mMinutes));
    return mins;
}

/**
 * Converts analog seconds to a string
 * @return seconds as type string
 */
std::string Clock::GetSeconds()
{
    std::string secs;

    if (mSeconds < 10)
    {
        secs = "0" + std::to_string(int(mSeconds));
    }
    else
    {
        secs = std::to_string(int(mSeconds));
    }

    return secs;
}

/**
 * Reset clock to zero
 */
void Clock::Reset()
{
    mMinutes = 0;
    mSeconds = 0;
}

/**
 * Draw the clock onto the Game
 * @param graphics The graphics context to draw on
 */
void Clock::Draw(std::shared_ptr<wxGraphicsContext> graphics, bool final)
{
    wxFont font(wxSize(ScoreboardTextSize, ScoreboardTextSize),
                wxFONTFAMILY_SCRIPT,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, wxColour(*wxWHITE));

    if(!final)
    {
        std::string analog = GetMinutes() + ":" + GetSeconds();
        graphics->DrawText(analog, ScoreboardTopLeft.x, ScoreboardTopLeft.y);
    }
    else
    {
        graphics->DrawText(GetScore(), ScoreboardTopLeft.x, ScoreboardTopLeft.y);
    }
}

void Clock::SetScore()
{
    mFinalScore = GetMinutes() + ":" + GetSeconds();
}

std::string Clock::GetScore()
{
    return mFinalScore;
}
