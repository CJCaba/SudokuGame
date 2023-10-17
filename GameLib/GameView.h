/**
 * @file GameView.h
 * @author jadec and Jason Lin
 *
 * View class for our game
 */

#ifndef ARES_GAMELIB_GAMEVIEW_H
#define ARES_GAMELIB_GAMEVIEW_H


#include <utility>

#include "Game.h"
#include "Clock.h"

class Clock;

/**
 * View class for our game
 */
class GameView : public wxWindow
{
private:
    // void OnFileOpen(wxCommandEvent &event);
    // void OnSaveAs(wxCommandEvent &event);
    // void OnLeftDown(wxMouseEvent &event);
    // void OnLeftUp(wxMouseEvent &event);
    void OnPaint(wxPaintEvent &event);
    void OnTimer(wxTimerEvent &event);


    /// An object that describes our game
    Game mGame;

    /// Clock allowing for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

public:
    void Initialize(wxFrame* parent);

    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}
};

#endif //ARES_GAMELIB_GAMEVIEW_H
