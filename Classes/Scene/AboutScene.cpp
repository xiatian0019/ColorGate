//
//  AboutScene.cpp
//  MagicSnake
//
//  Created by xiaoming on 15/12/30.
//
//

#include "AboutScene.hpp"

#include "GameSetting.h"
#include "GameTools.hpp"
#include "MainScene.hpp"
#include "SoundPlayer.hpp"
#include "Gate.hpp"
#include "Dialog.hpp"
Scene *AboutScene::createScene()
{
    auto scene = Scene::create();
    auto layer = AboutScene::create();
    scene->addChild(layer);
    return scene;
}


bool AboutScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    auto colorBack = LayerColor::create(Color4B(238, 237, 236, 255), WIDTH, HEIGHT);
    this->addChild(colorBack);
    
    aboutNode = Node::create();
    this->addChild(aboutNode);
    
    Label *label= Label::createWithSystemFont("XiaoHuiProject Present", FONT_VERDANA, 50);
    label->setColor(Gate::getColor3B(BLUE));
    this->addChild(label);
    label->setPosition(Vec2(WIDTH/2, HEIGHT/2+180));
    
    auto ourLabel = Label::createWithSystemFont(Dialog::getInstance()->getStringByID(TXT_MORE_GAME), FONT_VERDANA, 40);
    aboutNode->addChild(ourLabel);
    ourLabel->setPosition(Vec2(50, HEIGHT/2+20));
    ourLabel->setAnchorPoint(Vec2(0, 0.5));
    ourLabel->setColor(Gate::getColor3B(BLUE));
    
    auto snakeIcon = Sprite::create("snake.png");
    aboutNode->addChild(snakeIcon);
    snakeIcon->setPosition(Vec2(ourLabel->getPositionX()+snakeIcon->getContentSize().width/2, ourLabel->getPositionY()-150));
    
    auto snakeTitle = Label::createWithSystemFont("Magic Snake", FONT_VERDANA, 25);
    aboutNode->addChild(snakeTitle);
    snakeTitle->setColor(Gate::getColor3B(BLUE));
    snakeTitle->setAnchorPoint(Vec2(0, 1));
    snakeTitle->setPosition(Vec2(snakeIcon->getPositionX()+snakeIcon->getContentSize().width/2+25, snakeIcon->getPositionY()+snakeIcon->getContentSize().height/2-5));
    
    
    auto snakeDesc = Label::createWithSystemFont(Dialog::getInstance()->getStringByID(TXT_MORE_GAME_DESC), FONT_VERDANA, 25);
    snakeDesc->setAnchorPoint(Vec2(0, 1));
    snakeDesc->setPosition(Vec2(snakeTitle->getPositionX(), snakeTitle->getPositionY()-48));
    snakeDesc->setDimensions(WIDTH-30-snakeDesc->getPositionX(), 0);
    snakeDesc->setColor(Gate::getColor3B(BLUE));
    aboutNode->addChild(snakeDesc);
    
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(AboutScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(AboutScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    labelList.push_back(label);
    labelNum=0;
    if (GameTools::checkIsBirthDay()) {
        labelList.push_back(this->addSpecialLabel("Dear Hui~", Vec2(100, HEIGHT*4/5),Vec2(0, 0.5)));
        labelList.push_back(this->addSpecialLabel("Happy birthday and wishing you happiness every day!", Vec2(WIDTH/2, HEIGHT/2),Vec2(0.5, 0.5),true));
        labelList.push_back(this->addSpecialLabel("Ming~", Vec2(WIDTH-100, HEIGHT/5),Vec2(1, 0.5)));
        this->scheduleOnce(schedule_selector(AboutScene::specialStart), 8);
    }
    if (GameTools::getUserAge()<=3) {
        aboutNode->setVisible(false);
        label->setPosition(Vec2(WIDTH/2, HEIGHT/2));
    }
    return true;
}

bool AboutScene::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void AboutScene::onTouchEnded(Touch* touch, Event* event)
{
    SoundPlayer::btnPress();
    auto scene = MainScene::createScene();
    GameTools::changeToScene(scene, TRAN_FADE);
}

Label * AboutScene::addSpecialLabel(std::string labelTxt,Vec2 pos,Vec2 anchorPoint,bool setDimensions)
{
    auto label= Label::createWithSystemFont(labelTxt, FONT_VERDANA, 37);
    label->setAnchorPoint(anchorPoint);
    label->setColor(Gate::getColor3B(BLUE));
    this->addChild(label);
    if (setDimensions) {
        label->setDimensions(WIDTH-100,0);
        label->setAlignment(TextHAlignment::CENTER);
    }
    label->setPosition(pos);
    label->setVisible(false);
    return label;
}

void AboutScene::specialStart(float dt)
{
    auto label=labelList.at(labelNum);
    labelNum++;
    label->runAction(Sequence::create(FadeOut::create(1.5),DelayTime::create(0.5),CallFunc::create(CC_CALLBACK_0(AboutScene::specialCall, this)), NULL));
    
    
    auto list = aboutNode->getChildren();
    for (int i=0; i<list.size(); i++) {
        auto node = list.at(i);
        node->runAction(FadeOut::create(1.5));
    }
}

void AboutScene::specialCall()
{
    if (labelNum>=labelList.size()) {
        return;
    }
    auto label=labelList.at(labelNum);
    label->setColor(Gate::getColor3B(BLUE));
    label->setOpacity(0);
    label->setVisible(true);
    labelNum++;
    label->runAction(Sequence::create(FadeIn::create(1.5),DelayTime::create(0.5),CallFunc::create(CC_CALLBACK_0(AboutScene::specialCall, this)), NULL));
}