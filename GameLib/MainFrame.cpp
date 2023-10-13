/**
 * @file MainFrame.cpp
 * @authors Jason Lin
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
// #include "ids.h"

void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Game", wxDefaultPosition, wxSize(900,700));

    // Create a sizer that will lay out child windows vertically
    // one above the other
    auto sizer = new wxBoxSizer(wxVERTICAL);

    // Create the view class object as a child of MainFrame
    auto gameView = new GameView();
    gameView->Initialize(this);

    // Add it to the sizer and set for this frame
    sizer->Add(gameView, 1, wxEXPAND | wxALL);
    SetSizer(sizer);
    // Layout (place) the child windows
    Layout();
}