/**
 * @file GameView.h
 * @author jadec
 *
 * View class for our game
 */

#ifndef ARES_GAMELIB_GAMEVIEW_H
#define ARES_GAMELIB_GAMEVIEW_H

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

public:
    void Initialize(wxFrame* parent);

};

#endif //ARES_GAMELIB_GAMEVIEW_H
