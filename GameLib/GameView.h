/**
 * @file GameView.h
 * @author jadec, Daniel Flanagan
 *
 * View class for our game
 */

#ifndef ARES_GAMELIB_GAMEVIEW_H
#define ARES_GAMELIB_GAMEVIEW_H


#include "Game.h"
#include "Clock.h"


/**
 * View class for our game
 */
class GameView : public wxWindow
{
private:
    // void OnSaveAs(wxCommandEvent &event);
    // void OnLeftDown(wxMouseEvent &event);
    // void OnLeftUp(wxMouseEvent &event);
    void OnPaint(wxPaintEvent &event);
    void OnTimer(wxTimerEvent &event);


    /// An object that describes our game
    Game mGame;

    /// An object that stores hour and minute values
    Clock mClock;

    /// Clock allowing for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

public:
    void Initialize(wxFrame* parent);

    void OnFileOpen(wxCommandEvent &event);
};

#endif //ARES_GAMELIB_GAMEVIEW_H
