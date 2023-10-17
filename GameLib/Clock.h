/**
 * @file Clock.h
 * @author Jason Lin
 *
 * Clock holding elapsed time in seconds and minutes
 */

#ifndef ARES_GAMELIB_CLOCK_H
#define ARES_GAMELIB_CLOCK_H

class Game;

/**
 * Class for Analog Clock, converting ticks to hours and minutes
 */
class Clock
{
private:

/// The window clock is contained in
    Game *mGame;

    /// Minutes that have past since level start
    long mMinutes = 0;

    /// Seconds that have past since level start
    long mSeconds = 0;

public:
    Clock(Game *game);

    ~Clock();

    std::string GetMinutes();
    std::string GetSeconds();

    void SetTime(long elapsed);
    void Reset();
};

#endif //ARES_GAMELIB_CLOCK_H
