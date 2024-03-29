/**
 * @file AudioPlayer.h
 * @author Tyler Przybylo
 *
 * Audio Player
 */

#ifndef ARES_GAMELIB_AUDIOPLAYER_H
#define ARES_GAMELIB_AUDIOPLAYER_H

#include "Item.h"
#include "Clock.h"
#include <wx/sound.h>

/**
 * Audio Player for the game (loads from xml)
 */
class AudioPlayer : public Item
{
private:
    /// Pointer to the audio
    std::shared_ptr<wxSound> mAudio;

    /// Length of the audio
    double mAudioLength = 0;

    /// Clock used for timing the audio loop
    std::shared_ptr<Clock> mClock;

    /// Holds the start time for each audio loop
    int mStartTime = -1;

    /// Holds the end time for each audio loop
    int mEndTime = -1;

public:
    AudioPlayer(Game *game, wxXmlNode * dec, wxXmlNode* item);

    // Disables drawing because it is audio not an image
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Stop();

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(Visitor* visitor) override { visitor->VisitAudioPlayer(this); }
};

#endif //ARES_GAMELIB_AUDIOPLAYER_H
