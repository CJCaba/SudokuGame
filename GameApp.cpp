/**
 * @file GameApp.cpp
 * @authors Jason Lin
 */

#include "pch.h"
#include "GameApp.h"
#include <MainFrame.h>

/**
 * Initiates the Game Application
 * @return True if value, else False
 */
bool GameApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}