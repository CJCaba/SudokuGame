/**
 * @file GameApp.h
 * @authors Jason Lin
 *
 * Initiation of the Application
 */

#ifndef ARES__GAMEAPP_H
#define ARES__GAMEAPP_H

#include <wx/wx.h>

/**
 * Main Application Class
 */
class GameApp : public wxApp
{
private:

public:
    bool OnInit() override;
};

#endif //ARES__GAMEAPP_H
