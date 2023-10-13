/**
 * @file Timer.cpp
 * @author Jason Lin
 */

#include "Timer.h"

void Timer::Update(std::shared_ptr<wxGraphicsContext> gc)
{
    wxFont font(wxSize(0, 30),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    gc->SetFont(font, wxColour(0, 0, 0));
    gc->DrawText(L"0:00", 200, 0);
}