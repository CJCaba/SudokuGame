/**
 * @file GameView.h
 * @author jadec, Daniel Flanagan, and Jason Lin
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

    void OnFileOpen(wxCommandEvent &event);
    void OnFileSaveAs(wxCommandEvent &event);

    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}
};

#endif //ARES_GAMELIB_GAMEVIEW_H
