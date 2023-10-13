/**
 * @file MainFrame.cpp
 * @authors Jason Lin
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "ids.h"

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

    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    auto levelMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Choose level");
    menuBar->Append(helpMenu, L"&Help");

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
//    levelMenu->Append(IDM_LEVEL1, L"&Level 1", L"Start Level 1");
//    levelMenu->Append(IDM_LEVEL2, L"&Level 2", L"Start Level 2");
//    levelMenu->Append(IDM_LEVEL3, L"&Level 2", L"Start Level 2");

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);


    SetMenuBar(menuBar);

}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Application about box menu handler
 */
void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(L"Welcome to Sparty Action Sudoku!",
                 L"About the Game",
                 wxOK | wxCENTRE,
                 this);
}