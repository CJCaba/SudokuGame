/**
 * @file MainFrame.cpp
 * @authors Jason Lin
 *
 * The top level mainframe of the application
 */

#ifndef ARES_GAMELIB_MAINFRAME_H
#define ARES_GAMELIB_MAINFRAME_H

class GameView;

/**
 * Top Level Mainframe Class
 */
class MainFrame : public wxFrame
{
private:
    void OnExit(wxCommandEvent &event);

    void OnHelp(wxCommandEvent &event);
public:
    void Initialize();
};

#endif //ARES_GAMELIB_MAINFRAME_H
