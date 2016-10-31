//
//  GameOverPanel.cpp
//  MiniGameHor
//
//  Created by xiaoming on 16/6/28.
//
//

#include "GameOverPanel.hpp"
#include "cocos-ext.h"
USING_NS_CC_EXT;

#include "GameSetting.h"
#include "Dialog.hpp"

#include "GameTools.hpp"


GameOverPanel::GameOverPanel(int newScore)
{
    Layer::init();
    auto sp = ui::Scale9Sprite::create("gameOver.png");
    sp->setContentSize(Size(540, 300));
    sp->setOpacity(188);
    this->addChild(sp);
    sp->setPosition(Vec2(WIDTH/2, HEIGHT/2));
    auto title=Label::createWithSystemFont(Dialog::getInstance()->getStringByID(TXT_BATTLE_GAMEOVER), FONT_HELVETICA, 48);
    sp->addChild(title);
    title->setPosition(Vec2(sp->getContentSize().width/2, sp->getContentSize().height*2/3));

    
    auto label = Label::createWithSystemFont(Dialog::getInstance()->getStringByID(TXT_BATTLE_SCORE)+":"+Value(newScore).asString(), FONT_HELVETICA, 50);
    label->setPosition(Vec2(sp->getContentSize().width/2, sp->getContentSize().height/3));
    sp->addChild(label);
    this->autorelease();
}
GameOverPanel::~GameOverPanel()
{
    
}