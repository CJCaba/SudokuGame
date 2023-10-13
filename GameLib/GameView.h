/**
 * @file GameView.h
 * @author jadec
 *
 * View class for our game
 */

#ifndef ARES_GAMELIB_GAMEVIEW_H
#define ARES_GAMELIB_GAMEVIEW_H


#include "Game.h"


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
    // void OnTimer(wxTimerEvent &event);
    void OnPaint(wxPaintEvent &event);


    /// An object that describes our game
    Game mGame;

    /// Timer allowing for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;


public:
    void Initialize(wxFrame* parent);

};

#endif //ARES_GAMELIB_GAMEVIEW_H
