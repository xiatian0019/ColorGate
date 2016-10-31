//
//  SoundPlayer.cpp
//  MagicSnake
//
//  Created by xiaoming on 16/1/15.
//
//

#include "SoundPlayer.hpp"
#include "cocos2d.h"
USING_NS_CC;
#include <SimpleAudioEngine.h>
#include "GameSetting.h"

static bool mainBgm = false;
static bool firstPlay = true;

void SoundPlayer::playEffect(std::string fileName)
{
    if (!SoundPlayer::getSoundSwitch()) {
        return;
    }
    std::string soundName = fileName;
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
}

void SoundPlayer::btnPress()
{
    if (!SoundPlayer::getSoundSwitch()) {
        return;
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pressed.wav");
}

void SoundPlayer::playMainBgm()
{
    if (mainBgm) {
        return;
    }
    mainBgm=true;
    if (!SoundPlayer::getSoundSwitch()) {
        return;
    }
    if (firstPlay) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        firstPlay=false;
    }
//    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.8);
//    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(MAIN_BGM,true);
}
void SoundPlayer::playBattleBgm()
{
    if (!mainBgm) {
        return;
    }
    mainBgm=false;
    if (!SoundPlayer::getSoundSwitch()) {
        return;
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("battleBGM1.mp3",true);
}


void SoundPlayer::soundOn()
{
    if (SoundPlayer::getSoundSwitch()) {
        return;
    }
    UserDefault::getInstance()->setBoolForKey("SoundSwitch", true);
    UserDefault::getInstance()->flush();
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    
}
void SoundPlayer::soundOff()
{
    if (!SoundPlayer::getSoundSwitch()) {
        return;
    }
    UserDefault::getInstance()->setBoolForKey("SoundSwitch", false);
    UserDefault::getInstance()->flush();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

bool SoundPlayer::getSoundSwitch()
{
    bool soundSwitch = UserDefault::getInstance()->getBoolForKey("SoundSwitch", true);
    UserDefault::getInstance()->flush();
    return soundSwitch;
}

