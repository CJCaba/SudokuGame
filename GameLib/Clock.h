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
    double mMinutes = 0;

    /// Seconds that have past since level start
    double mSeconds = 0;

    /// The final score of the game
    std::string mFinalScore;

public:
    /// Default constructor (disabled)
    Clock() = delete;

    /// Copy constructor (disabled)
    Clock(const Clock &) = delete;

    /// Assignment operator
    void operator=(const Clock &) = delete;

    Clock(Game *game);

    ~Clock();

    std::string GetMinutes();
    std::string GetSeconds();

    void SetTime(long time);
    void AddTime(double elapsed);
    void Reset();
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, bool final = false);
    void SetScore();
    std::string GetScore();
};

#endif //ARES_GAMELIB_CLOCK_H
