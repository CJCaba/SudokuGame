/**
 * @file MainFrame.cpp
 * @authors Jason Lin
 */

#include "pch.h"
#include "MainFrame.h"

void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Game", wxDefaultPosition, wxSize(900,700));
}