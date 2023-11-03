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

    std::string GetSeconds();

    void SetTime(long time);
    void AddTime(double elapsed);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, bool final = false);

    /**
     * Converts analog minutes to a string
     * @return minutes as type string
     */
    std::string GetMinutes() { std::string mins = std::to_string(int(mMinutes)); return mins; }

    /**
     * Reset clock to zero
     */
    void Reset() { mMinutes = 0; mSeconds = 0; }

    /**
     * Set the final score of the game
     */
    void SetScore() { mFinalScore = GetMinutes() + ":" + GetSeconds(); }

    /**
     * Return the final score in string form
     * @return final score
     */
    std::string GetScore() { return mFinalScore; }
};

#endif //ARES_GAMELIB_CLOCK_H
