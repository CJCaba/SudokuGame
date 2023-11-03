/**
 * @file VisitorAudio.h
 * @author Tyler Przybylo
 *
 * Visitor for Audio Player
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
    /// Pointer for AudioPlayer item
    AudioPlayer* mAudio = nullptr;
public:
    /**
     * Visits AudioPlayer instance
     * @param audio instance of AudioPlayer
     */
    void VisitAudioPlayer(AudioPlayer* audio) { mAudio = audio; }

    /**
     * Visit an AudioPlayer item
     * @param audio Pointer to an AudioPlayer
     */
    void VisitAudioPlayer(AudioPlayer* audio)
    {
        mAudio = audio;
    }

    /**
     * Return AudioPlayer pointer
     * @return mAudio
     */
    AudioPlayer* AudioFound()
    {
        return mAudio;
    }
};

#endif //ARES_GAMELIB_VISITORAUDIO_H
