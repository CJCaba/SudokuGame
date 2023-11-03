/**
 * @file VisitorAudio.h
 * @author Tyler Przybylo
 *
 *
 */

#ifndef ARES_GAMELIB_VISITORAUDIO_H
#define ARES_GAMELIB_VISITORAUDIO_H

#include "Visitor.h"

/**
 * Visitor that identifies and retrieves a AudioPlayer instance
 */
class VisitorAudio : public Visitor
{
private:
    AudioPlayer* mAudio = nullptr;
public:
    /**
     * Visits AudioPlayer instance
     * @param audio instance of AudioPlayer
     */
    void VisitAudioPlayer(AudioPlayer* audio) { mAudio = audio; }

    /**
     * Getter for AudioPLayer instance
     * @return AudioPLayer instance
     */
    AudioPlayer* AudioFound()
    {
        return mAudio;
    }
};

#endif //ARES_GAMELIB_VISITORAUDIO_H
