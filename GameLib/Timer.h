/**
 * @file Timer.h
 * @author Jason Lin
 *
 *
 */

#ifndef ARES_GAMELIB_TIMER_H
#define ARES_GAMELIB_TIMER_H

#include "Game.h"

class Timer
{
private:
    int mMinute = 0;
    int mSecond = 0;
public:
    int GetMinutes(){return mMinute;}
    int GetSeconds(){return mSecond;}
};

#endif //ARES_GAMELIB_TIMER_H
