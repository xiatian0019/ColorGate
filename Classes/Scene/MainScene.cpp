//
//  MainScene.cpp
//  MiniGameHor
//
//  Created by xiaoming on 16/6/23.
//
//

#include "MainScene.hpp"
#include "ADCenter.hpp"
#include "SoundPlayer.hpp"
#include "GameCenter.hpp"
#include "GameSetting.h"
#include "BattleScene.hpp"
#include "GameTools.hpp"
#include "Dialog.hpp"
#include "HelpScene.hpp"
#include "AboutScene.hpp"
#include "Gate.hpp"

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->setButtons();
    return true;
};

void MainScene::onEnter()
{
    Layer::onEnter();
    this->scheduleOnce(schedule_selector(MainScene::userEvaluate), 0.15);
}

void MainScene::userEvaluate(float dt)
{
    ADCenter::getInstance()->userEvaluate();
}

void MainScene::setButtons()
{
    auto colorBack = LayerColor::create(Color4B(238, 237, 236, 255), WIDTH, HEIGHT);
    this->addChild(colorBack);
    
    
    labelTitle = Label::createWithSystemFont(Dialog::getInstance()->getStringByID(TXT_MAIN_TITLE), FONT_VERDANA, 75);
    labelTitle->setPosition(Vec2(WIDTH/2+10, HEIGHT*4/5-10));
    this->addChild(labelTitle);
    labelTitle->setColor(Color3B(205, 105, 201));
    
    
    auto labelStart=Label::createWithSystemFont(Dialog::getInstance()->getStringByID(TXT_MAIN_START), FONT_VERDANA, 52);
    auto labelHelp=Label::createWithSystemFont(Dialog::getInstance()->getStringByID(TXT_MAIN_HELP), FONT_VERDANA, 52);
    auto labelAbout=Label::createWithSystemFont(Dialog::getInstance()->getStringByID(TXT_MAIN_ABOUT), FONT_VERDANA, 52);
    
    auto itemStart = MenuItemLabel::create(labelStart, CC_CALLBACK_1(MainScene::onStartClick, this));
    auto itemHelp = MenuItemLabel::create(labelHelp, CC_CALLBACK_1(MainScene::onHelpClick, this));
    auto itemAbout = MenuItemLabel::create(labelAbout, CC_CALLBACK_1(MainScene::onAboutClick, this));
    
    

    itemStart->setColor(Gate::getColor3B(RED));
    itemHelp->setColor(Gate::getColor3B(YELLOW));
    itemAbout->setColor(Gate::getColor3B(BLUE));
    
    
    
    //rank
    auto itemRank=MenuItemImage::create("btnRankNormal.png", "btnRankPressed.png", CC_CALLBACK_1(MainScene::onRankClick, this));
    itemRank->setPosition(Vec2(-WIDTH/2+itemRank->getContentSize().width/2+35, -HEIGHT/2+60));
    
    //sound
    soundOn=MenuItemImage::create("btnSoundOn.png", "btnSoundOnPressed.png", CC_CALLBACK_1(MainScene::soundOffClick, this));
    soundOff=MenuItemImage::create("btnSoundOff.png", "btnSoundOffPressed.png", CC_CALLBACK_1(MainScene::soundOnClick, this));
    soundOn->setPosition(Vec2(WIDTH/2-soundOn->getContentSize().width/2-35, -HEIGHT/2+60));
    soundOff->setPosition(Vec2(WIDTH/2-soundOn->getContentSize().width/2-35, -HEIGHT/2+60));
    
    this->updateSoundSwitch(SoundPlayer::getSoundSwitch());

    
    itemHelp->setPosition(Vec2(0, -HEIGHT/6));
    itemAbout->setPosition(Vec2(0, -HEIGHT*2/6));
    
    auto menu = Menu::create(itemStart,itemHelp,itemAbout,itemRank,soundOn,soundOff,NULL);
    this->addChild(menu);
    
    
    SoundPlayer::playMainBgm();
    
    GameCenter::login();
    ADCenter::getInstance()->setBannerHide(true);
}



void MainScene::onStartClick(Ref *ref)
{
    SoundPlayer::btnPress();
    auto scene = BattleScene::createScene();
    GameTools::changeToScene(scene, TRAN_FADE);
}
void MainScene::onHelpClick(Ref *ref)
{
    SoundPlayer::btnPress();
    auto scene = HelpScene::createScene();
    GameTools::changeToScene(scene, TRAN_FADE);
}
void MainScene::onAboutClick(Ref *ref)
{
    SoundPlayer::btnPress();
    auto scene = AboutScene::createScene();
    GameTools::changeToScene(scene, TRAN_FADE);
}

void MainScene::onRankClick(Ref *ref)
{
    GameCenter::showRank();
}
void MainScene::soundOnClick(Ref *ref)
{
    SoundPlayer::soundOn();
    SoundPlayer::btnPress();
    this->updateSoundSwitch(true);
}
void MainScene::soundOffClick(Ref *ref)
{
    SoundPlayer::soundOff();
    this->updateSoundSwitch(false);
}

void MainScene::updateSoundSwitch(bool soundOn)
{
    this->soundOn->setVisible(soundOn);
    this->soundOff->setVisible(!soundOn);
}