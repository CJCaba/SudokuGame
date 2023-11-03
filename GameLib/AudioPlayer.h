/**
 * @file AudioPlayer.h
 * @author Tyler Przybylo
 *
 * Audio Player
 */

#ifndef ARES_GAMELIB_AUDIOPLAYER_H
#define ARES_GAMELIB_AUDIOPLAYER_H

#include "Item.h"
#include <wx/sound.h>

/**
 * Audio Player for the game (loads from xml)
 */
class AudioPlayer : public Item
{
private:
    wxSound mAudio;
public:
    /// Constructor
    AudioPlayer(Game *game, wxXmlNode * dec, wxXmlNode* item);

    // Disables drawing because it is audio not an image
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override {};

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(Visitor* visitor) override { visitor->VisitAudioPlayer(this); }
};

#endif //ARES_GAMELIB_AUDIOPLAYER_H
