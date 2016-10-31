//
//  HelpScene.cpp
//  ColorGate
//
//  Created by xiaoming on 16/5/5.
//
//

#include "HelpScene.hpp"
#include "GameSetting.h"
#include "GameTools.hpp"
#include "MainScene.hpp"
#include "SoundPlayer.hpp"
#include "Dialog.hpp"
#include "Gate.hpp"

Scene* HelpScene::createScene()
{
    auto scene = Scene::create();
    auto layer = HelpScene::create();
    scene->addChild(layer);
    return scene;
}
bool HelpScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto colorBack = LayerColor::create(Color4B(238, 237, 236, 255), WIDTH, HEIGHT);
    this->addChild(colorBack);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(HelpScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelpScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    auto label=Label::createWithSystemFont(Dialog::getInstance()->getStringByID(TXT_MAIN_HELP), FONT_VERDANA, 65);
    this->addChild(label);
    label->setPosition(Vec2(WIDTH/2, HEIGHT*5/6));
    label->setColor(Gate::getColor3B(BLUE));
    
    float posY=HEIGHT-(HEIGHT/6)*2.2+20;
    
    float dif=50;
    float fontSize =35;
    if (Dialog::getInstance()->getIsChinese()) {
        dif=80;
        fontSize=42;
    }
    posY=this->addHelpLabel(Dialog::getInstance()->getStringByID(TXT_HELP_1), Vec2(WIDTH/2, posY),fontSize)-dif;
    posY=this->addHelpLabel(Dialog::getInstance()->getStringByID(TXT_HELP_2), Vec2(WIDTH/2, posY),fontSize)-dif;
    this->addHelpLabel(Dialog::getInstance()->getStringByID(TXT_HELP_3), Vec2(WIDTH/2, posY),fontSize);
    
    
    return true;
}


bool HelpScene::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void HelpScene::onTouchEnded(Touch* touch, Event* event)
{
    SoundPlayer::btnPress();
    auto scene = MainScene::createScene();
    GameTools::changeToScene(scene, TRAN_FADE);
}


float HelpScene::addHelpLabel(std::string labelTxt,Vec2 pos,float fontSize)
{
    auto label= Label::createWithSystemFont(labelTxt,FONT_VERDANA, fontSize);
    this->addChild(label);
    label->setPosition(pos);
    label->setDimensions(WIDTH-100, 0);
    label->setAnchorPoint(Vec2(0.5, 1));
    label->setColor(Gate::getColor3B(BLUE));
    float posY=pos.y-label->getContentSize().height;
    return posY;
}