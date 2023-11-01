/**
 * @file ImFullErrorMessage.cpp
 * @author Gerald Hoskins
 */

#include <string>
#include "ImFullErrorMessage.h"

using namespace std;

/// Error Message Text
const wxString ErrorMessage("I'm Full!");

/// Vertical speed in pixels per second
const double ErrorMessageSpeed = 200;

/// Width of the error message
const double ErrorMessageWidth = 100;

/// Height of the error message
const double ErrorMessageHeight = 50;

ImFullErrorMessage::ImFullErrorMessage(wxPoint position)
{
    mPosition = position;
}

void ImFullErrorMessage::Update(double elapsed)
{
    // Update vertical position
    mPosition.y -= ErrorMessageSpeed * elapsed;

    if (mPosition.y < 0)
        mDeleteMeFlag = true;
}

void ImFullErrorMessage::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Rectangle properties
    wxPoint topLeft(mPosition.x - ErrorMessageWidth / 2, mPosition.y - ErrorMessageHeight / 2);
    wxSize rectSize(ErrorMessageWidth, ErrorMessageHeight);

    // Create a white brush and set it
    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);

    // Create a black pen and set it
    wxPen rectPen(*wxBLACK, 2); // 1 is the pen width
    graphics->SetPen(rectPen);

    // Draw a white rectangle with a black border
    graphics->DrawRectangle(topLeft.x, topLeft.y, rectSize.x, rectSize.y);

    // Create a font and set it
    wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxColour textColor(*wxRED);
    graphics->SetFont(font, textColor);

    // Calculate the text position to center it within the rectangle
    double textWidth, textHeight;
    graphics->GetTextExtent(ErrorMessage, &textWidth, &textHeight);
    wxPoint textPosition(topLeft.x + (rectSize.x - textWidth) / 2, topLeft.y + (rectSize.y - textHeight) / 2);

    // Draw the red text in the center of the rectangle
    graphics->DrawText(ErrorMessage, textPosition.x, textPosition.y);
}

