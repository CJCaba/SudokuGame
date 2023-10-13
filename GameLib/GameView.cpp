/**
 * @file GameView.cpp
 * @author jadec
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
    Create(parent, wxID_ANY, wxDefaultPosition,
           wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent &event) {
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto gc =
        std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    wxRect rect = GetRect();
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());
}