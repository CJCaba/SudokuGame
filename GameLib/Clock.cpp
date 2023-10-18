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
 * @param gameView The window this clock is a member of
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
 * @param elapsed time since stopwatch started
 */
void Clock::SetTime(long time)
{
    mSeconds = time / 1000;
    mMinutes = mSeconds / 60;

    if(mSeconds >= 60)
    {
        mSeconds -= mMinutes * 60;
    }
}

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

void Clock::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    double xOffset = mGame->GetXOffset();
    double yOffset = mGame->GetYOffset();
    double scale = mGame->GetScale();

    wxFont font(wxSize(ScoreboardTextSize * scale, ScoreboardTextSize * scale),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, wxColour(*wxWHITE));

    std::string analog = GetMinutes() + ":" + GetSeconds();
    graphics->DrawText(analog, xOffset + ScoreboardTopLeft.x * scale, yOffset + ScoreboardTopLeft.y * scale);
}
