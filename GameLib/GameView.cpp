/**
 * @file GameView.cpp
 * @author jadec, Daniel Flanagan
 */

#include "pch.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include "GameView.h"
 #include "ids.h"

using namespace std;

/**
 * Initialize the game view class.
 * @param parent The parent window for this class
*/
void GameView::Initialize(wxFrame *parent) {
    // Redefine Create function to allow for the use of virtual pixels
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);

    SetBackgroundStyle(wxBG_STYLE_PAINT);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnFileSaveAs, this,
                 wxID_SAVEAS);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnFileOpen, this,
                 wxID_OPEN);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel1, this,
                 IDM_LEVELONE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel2, this,
                 IDM_LEVELTWO);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevel3, this,
                 IDM_LEVELTHREE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnSolve, this,
                 IDM_SOLVE);

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);
    Bind(wxEVT_MOTION, &GameView::OnMouseMove, this);

    mTimer.SetOwner(this);
    mTimer.Start(1); //< Set to 1 to avoid error on MacOS
    mStopWatch.Start();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent &event) {
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    // Create a graphics context
    auto gc =
        std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    wxRect rect = GetClientRect();

    auto minDimension = min(rect.GetWidth(), rect.GetHeight());
    if(minDimension == 0)
    {
        // No reason to draw if the window is size zero
        // and this avoids any divid by zero errors
        return;
    }
    gc->PushState();

    mGame.OnUpdate(elapsed);    //<-Update
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());

    gc->PopState();
}

/**
 * Handle timer events
 * @param event timer event
 */
void GameView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}

/**
 * Handle the left mouse button down event
 * @param event The mouse event
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{
    mGame.OnLeftDown(event);
}

/**
 * Handle the key down event
 * @param event The key event
 */
void GameView::OnKeyDown(wxKeyEvent &event)
{
    mGame.OnKeyDown(event);
}

/**
 * Handle Mouse movement
 * @param event the mouse event
 */
 void GameView::OnMouseMove(wxMouseEvent &event)
{
     mGame.OnMouseMove(event);
}

/**
 * Handle the File>Save As menu option
 * @param event The menu event
 */
void GameView::OnFileSaveAs(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, L"Save Game file", L"", L"",
                                L"Game Files (*.xml)|*.xml", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = saveFileDialog.GetPath();
    mGame.Save(filename);
}

/**
 * File>Open menu handler
 * @param event Menu event
 */
void GameView::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, L"Load Game file", L"", L"",
                                L"Game Files (*.xml)|*.xml", wxFD_OPEN);
    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = loadFileDialog.GetPath();
    mGame.Load(filename);
    Refresh();
}

/**
 * Choose Level>Level 1
 * @param event Menu event
 */
 void GameView::OnLevel1(wxCommandEvent &event)
 {
    mGame.SetLevel(L"LevelFiles/level1.xml");
 }

/**
* Choose Level>Level 2
* @param event Menu event
*/
void GameView::OnLevel2(wxCommandEvent &event)
{
    mGame.SetLevel(L"LevelFiles/level2.xml");
}

/**
 * Choose Level>Level 3
 * @param event Menu event
 */
void GameView::OnLevel3(wxCommandEvent &event)
{
    mGame.SetLevel(L"LevelFiles/level3.xml");
}

/**
 * Solve the board with current numbers
 * @param event Menu event
*/
void GameView::OnSolve(wxCommandEvent &event){
    mGame.Solve();
}