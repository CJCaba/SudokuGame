/**
 * @file Clock.cpp
 * @author Jason Lin
 */

#include "pch.h"
#include "Clock.h"
#include "Game.h"

/**
 * Constructor
 * @param gameView The window this clock is a member of
 */
Clock::Clock(Game *game)
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

/**
 * Converts analog minutes to a string
 * @return minutes as type string
 */
std::string Clock::GetMinutes()
{
    std::string hrs = std::to_string(mMinutes);
    return hrs;
}

/**
 * Converts analog seconds to a string
 * @return seconds as type string
 */
std::string Clock::GetSeconds()
{
    std::string mins;

    if (mSeconds < 10)
    {
        mins = "0" + std::to_string(mSeconds);
    }
    else
    {
        mins = std::to_string(mSeconds);
    }

    return mins;
}

/**
 * Reset clock to zero
 */
void Clock::Reset()
{
    mMinutes = 0;
    mSeconds = 0;
}