/**
 * @file VisitorAudio.h
 * @author Tyler Przybylo
 *
 *
 */

#ifndef ARES_GAMELIB_VISITORAUDIO_H
#define ARES_GAMELIB_VISITORAUDIO_H

#include "Visitor.h"

class VisitorAudio : public Visitor
{
private:
    AudioPlayer* mAudio = nullptr;
public:
    void VisitAudioPlayer(AudioPlayer* audio)
    {
        mAudio = audio;
    }

    AudioPlayer* AudioFound()
    {
        return mAudio;
    }
};

#endif //ARES_GAMELIB_VISITORAUDIO_H
