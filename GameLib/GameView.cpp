/**
 * @file GameView.cpp
 * @author jadec
 */

#include "pch.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include "GameView.h"
// #include "ids.h"

using namespace std;

/**
 * Initialize the game view class.
 * @param parent The parent window for this class
*/
void GameView::Initialize(wxFrame *parent) {
    // Redefine Create function to allow for the use of virtual pixels
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);

    mTimer.SetOwner(this);
    mTimer.Start();
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

    //
    // Convert wxStopwatch time to Analog
    //
    mClock.SetTime(mTime);

    //
    // Update
    //
    // mGame.OnUpdate(elapsed);


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

    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight(), mClock);
}

/**
 * Handle timer events
 * @param event timer event
 */
void GameView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}