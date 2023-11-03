/**
 * @file AudioPlayer.cpp
 * @author Tyler Przybylo
 */

#include "pch.h"

#include "AudioPlayer.h"

/**
 * Constructor
 * @param game The game this spotlight is a member of
 * @param dec The declaration node containing all the information to create a basic spotlight
 * @param item The item node containing the location information for this specific spotlight
 */
AudioPlayer::AudioPlayer(Game *game, wxXmlNode * dec, wxXmlNode* item) : Item(game, dec, item)
{
    std::wstring filename = L"audio/" + dec->GetAttribute("file", "").ToStdWstring();
    mAudio = std::make_shared<wxSound>(filename);
    dec->GetAttribute("length", "0").ToDouble(&mAudioLength);

    mClock = game->GetClock();
}

/**
 * Override draw to play audio instead
 * @param graphics graphics context of the game
 */
void AudioPlayer::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mAudio->IsOk())
    {
        if(mStartTime == -1)
        {
            mStartTime = std::stoi(mClock->GetSeconds());
            mEndTime = mStartTime + mAudioLength;
            mAudio->Play();
        }

        int currentTime = std::stoi(mClock->GetSeconds());
        if (currentTime >= mEndTime)
        {
            mStartTime = -1;
        }
    }
}

/**
* Stops the audio
*/
void AudioPlayer::Stop()
{
    mAudio->Stop();
}