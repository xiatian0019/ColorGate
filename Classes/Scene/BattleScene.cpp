//
//  BattleScene.cpp
//  ColorGate
//
//  Created by xiaoming on 16/4/28.
//
//

#include "BattleScene.hpp"
#include "GameTools.hpp"
#include "SoundPlayer.hpp"
#include "MainScene.hpp"
#include "ADCenter.hpp"
#include "Dialog.hpp"
#include "GameCenter.hpp"

Scene* BattleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = BattleScene::create();
    scene->addChild(layer);
    return scene;
}
bool BattleScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    hourglass=NULL;
    auto colorBack = LayerColor::create(Color4B(238, 237, 236, 255), WIDTH, HEIGHT);
    this->addChild(colorBack);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(false);
    touchListener->onTouchBegan = CC_CALLBACK_2(BattleScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(BattleScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    auto scoreBack = Sprite::create("scoreBack.png");
    scoreBack->setAnchorPoint(Vec2(0, 1));
    this->addChild(scoreBack);
    scoreBack->setPosition(Vec2(50, HEIGHT-50));
    
    
    labelScore=Label::createWithSystemFont("",FONT_HELVETICA_BOLD, 22);
    scoreBack->addChild(labelScore);
    labelScore->setAnchorPoint(Vec2(0, 0.5));
    labelScore->setPosition(Vec2(90, scoreBack->getContentSize().height/2));
    myGateGroup=NULL;
    
    gameOverTips=Label::createWithSystemFont(Dialog::getInstance()->getStringByID(TXT_BATTLE_START_TIPS), FONT_GEORGIA, 65);
    this->addChild(gameOverTips);
    gameOverTips->setPosition(Vec2(WIDTH/2, HEIGHT/2-20));
    gameOverTips->setColor(Color3B(205, 105, 201));
    
    
    auto timeBack = Sprite::create("timeBack.png");
    this->addChild(timeBack);
    timeBack->setAnchorPoint(Vec2(1, 1));
    timeBack->setPosition(Vec2(WIDTH-50, HEIGHT-50));
    
    hourglass= Sprite::create("hourglass1.png");
    timeBack->addChild(hourglass);
    hourglass->setPosition(Vec2(40, timeBack->getContentSize().height/2));
    
    gameOverPanel=NULL;
    particleSystem=NULL;
    
    gameTimeLabel=Label::createWithSystemFont("", FONT_HELVETICA_BOLD, 22);
    gameTimeLabel->setAnchorPoint(Vec2(0, 0.5));
    gameTimeLabel->setPosition(Vec2(100, timeBack->getContentSize().height/2));
    timeBack->addChild(gameTimeLabel);
    
    
    gameRunningTips=new StageTip(NONE,ANY);
    this->addChild(gameRunningTips);
    gameRunningTips->setPosition(Vec2(WIDTH/2, HEIGHT-160));
    gameRunningTips->setVisible(false);
    this->resetGame();
    this->schedule(schedule_selector(BattleScene::secondFrame), 0.1f);
    this->addSnow();
    SoundPlayer::playBattleBgm();
    
    
    auto itemBack = MenuItemImage::create("btnBack.png", "btnBack.png", CC_CALLBACK_1(BattleScene::backClick, this));
    auto menu = Menu::create(itemBack, NULL);
    this->addChild(menu);
    itemBack->setPosition(Vec2(100-WIDTH/2, 100-HEIGHT/2));
    
    //init animation
    auto animation = Animation::create();
    for (int i=0; i<3; i++) {
        animation->addSpriteFrameWithFile("hourglass"+Value(i+1).asString()+".png");
    }
    animation->setDelayPerUnit(0.4f);
    AnimationCache::getInstance()->addAnimation(animation, "hourglass");
    
    ADCenter::getInstance()->setBannerHide(false);
    
    return true;
}


void BattleScene::hourGlassAnimeRun()
{
    if (hourglass==NULL) {
        return;
    }
    auto animation = AnimationCache::getInstance()->getAnimation("hourglass");
    auto anime = Animate::create(animation);
    auto delay = DelayTime::create(0.25);
    auto rotateBy = RotateBy::create(0.5, 180);
    auto rotateTo = RotateTo::create(0, 0);
    
    //auto call = CallFunc::create(CC_CALLBACK_0(BattleScene::resetHourglass, this));

    auto seq = Sequence::create(anime,delay,rotateBy,rotateTo,NULL);
    auto repeat =RepeatForever::create(seq);
    hourglass->runAction(repeat);
    
}
void BattleScene::resetHourglass()
{
    //hourglass->setTexture("hourglass1.png");
    hourglass->setRotation(0);
}

void BattleScene::hourGlassAnimeStop()
{
    if (hourglass==NULL) {
        return;
    }
    hourglass->stopAllActions();
    this->resetHourglass();
    
}


void BattleScene::backClick(Ref *ref)
{
    SoundPlayer::btnPress();
    auto scene = MainScene::createScene();
    GameTools::changeToScene(scene, TRAN_FADE);
}
void BattleScene::onExit()
{
    if (particleSystem) {
        particleSystem->stopSystem();
    }
    Layer::onExit();
}


void BattleScene::addSnow()
{
    return;
    particleSystem = ParticleSnow::createWithTotalParticles(1500);
    particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage("snow.png"));
    this->addChild(particleSystem);
    particleSystem->setPosition(Vec2(WIDTH/2, HEIGHT));
    particleSystem->setSpeed(100);
    particleSystem->setGravity(Vec2(0, -HEIGHT));
}

void BattleScene::secondFrame(float dt)
{
    if (!gameRunning) {
        return;
    }
    int randomTime=GameTools::getRandomNum(5, 15);
    gameTime=gameTime-randomTime;
    if (gameTime<=0) {
        gameTime=0;
        this->gameOver();
    }
    std::string strSec1="00";
    if (gameTime/100>=10) {
        strSec1=Value(gameTime/100).asString();
    }
    else{
        strSec1="0"+Value(gameTime/100).asString();
    }
    std::string strSec2="00";
    if (gameTime%100>=10) {
        strSec2=Value(gameTime%100).asString();
    }
    else{
        strSec2="0"+Value(gameTime%100).asString();
    }
    std::string strTime=strSec1+":"+strSec2;
    gameTimeLabel->setString(strTime);
}

void BattleScene::resetGame()
{
    gameRunning=false;
    myScore=0;
    currentColor=ANY;
    currentPos=NONE;
    this->updateLabels();
    gameTime=GAME_TIME;
}

void BattleScene::updateGateGroup()
{
    CCLOG("LXM-BattleScene-updateGateGroup-START");
    this->removeGateGroup();
    CCLOG("LXM-BattleScene-removeGateGroup-END");
    gameRunningTips->setVisible(true);
    CCLOG("LXM-BattleScene-newGateGroup-START");
    myGateGroup = new GateGroup(currentColor);
    CCLOG("LXM-BattleScene-newGateGroup-END");
    this->addChild(myGateGroup);
    myGateGroup->setDelegate(this);
    myGateGroup->setPosition(Vec2(0, -65));
    CCLOG("LXM-BattleScene-newGateGroup-END111");
}

void BattleScene::removeGateGroup()
{
    if (myGateGroup) {
        // remove anime?
        myGateGroup->removeFromParent();
        myGateGroup=NULL;
    }
}

void BattleScene::gateCorrect(GATE_COLOR newColor,int lastPos)
{
    gameTime=gameTime+100;
    myScore++;
    currentColor=newColor;
    currentPos=(GATE_POS)lastPos;
    this->updateLabels();
    this->updateGateGroup();
}
void BattleScene::gateWrong()
{
    this->gameOver();
}

void BattleScene::gatePress(GATE_COLOR gateColor,Vec2 point)
{
    int colorId = (int)gateColor+1;
    if (colorId<1 || colorId>3) {
        return;
    }
    std::string fileName="explosion"+Value(colorId).asString()+".plist";
    ParticleSystemQuad *effect = ParticleSystemQuad::create(fileName);
    this->addChild(effect,1000);
    effect->setAutoRemoveOnFinish(true);
    effect->setPosition(point);
}

void BattleScene::addGameOverPanel(int score)
{
    if (gameOverPanel) {
        return;
    }
    gameOverPanel = new GameOverPanel(score);
    this->addChild(gameOverPanel);
}


void BattleScene::gameOver()
{
    this->addGameOverPanel(myScore);
    GameCenter::uploadScore(myScore);
    this->resetGame();
    this->removeGateGroup();
    gameRunningTips->setVisible(false);;
    this->hourGlassAnimeStop();
    this->scheduleOnce(schedule_selector(BattleScene::addAd), 0.2);
}

void BattleScene::addAd(float dt)
{
    ADCenter::getInstance()->addFullScreen();
}

void BattleScene::updateLabels()
{
    std::string strScore=Dialog::getInstance()->getStringByID(TXT_BATTLE_SCORE)+":"+Value(myScore).asString();
    labelScore->setString(strScore);
    gameRunningTips->updateState(currentPos,currentColor);
}
bool BattleScene::onTouchBegan(Touch* touch, Event* event)
{
    return !gameRunning;
}
void BattleScene::onTouchEnded(Touch* touch, Event* event)
{
    if (gameOverPanel) {
        gameOverPanel->removeFromParent();
        gameOverPanel=NULL;
    }
    gameRunning=true;
    gameOverTips->setVisible(false);
    this->updateGateGroup();
    this->hourGlassAnimeRun();
}

void BattleScene::aniTimeAddAnime()
{
    auto label = Label::createWithSystemFont("+1s", FONT_GEORGIA, 50);
    this->addChild(label,500);
    label->setPosition(Vec2(WIDTH/2, HEIGHT/2));
    //auto
}
