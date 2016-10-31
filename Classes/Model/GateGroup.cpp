//
//  GateGroup.cpp
//  ColorGate
//
//  Created by xiaoming on 16/4/28.
//
//

#include "GateGroup.hpp"
#include "GameTools.hpp"
#include "SoundPlayer.hpp"

GateGroup::GateGroup(GATE_COLOR correctColor)
{
    Layer::init();
    myDelegate=NULL;
    this->correctColor=correctColor;
    this->addGate();
    this->openTouchEvent();
    this->autorelease();
}

void GateGroup::setDelegate(GateGroupDelegate *delegate)
{
    myDelegate=delegate;
}

void GateGroup::addGate()
{
    int randomPos=GameTools::getRandomNum(0, 2);
    for (int i=0; i<3; i++) {
        GATE_COLOR color=(GATE_COLOR)GameTools::getRandomNum(0, 2);
        if (i==randomPos&&correctColor!=ANY) {
            color=correctColor;
        }
        auto gate = new Gate(color,(GATE_POS)i);
        this->addChild(gate);
        gate->setPosition(Vec2(WIDTH*(i+1)/4, HEIGHT/2));
        gateList.push_back(gate);
    }
    this->gateOpenAnime();
}

void GateGroup::gateOpenAnime()
{
    for (int i=0; i<gateList.size(); i++) {
        gateList.at(i)->gateFadeIn();
    }
}


void GateGroup::openTouchEvent()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(false);
    touchListener->onTouchBegan = CC_CALLBACK_2(GateGroup::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GateGroup::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
bool GateGroup::onTouchBegan(Touch* touch, Event* event)
{
    startPoint=touch->getLocation();
    return true;
}
void GateGroup::onTouchEnded(Touch* touch, Event* event)
{
    Vec2 endPoint=touch->getLocation();
    if (fabsf(startPoint.x-endPoint.x)>PRESS_MAX_DIF||fabsf(startPoint.y-endPoint.y)>PRESS_MAX_DIF) {
        return;
    }
    
    for (int i=0; i<gateList.size(); i++) {
        auto gate = gateList.at(i);
        if (gate->getBoundingBox().containsPoint(endPoint)) {
            //this->addExplosionEffect(gate->getGateColor(), gate->getPosition());
            SoundPlayer::playEffect(gate->getPressSoundEffect());
            this->gatePressed(correctColor==ANY||gate->getGateColor()==correctColor,gate->getGateColor(),gate->getPosition());
            break;
        }
    }
}

void GateGroup::gatePressed(bool correct,GATE_COLOR pressedColor,Vec2 gatePos)
{
    if (myDelegate==NULL) {
        return;
    }
    if (!correct) {
        myDelegate->gateWrong();
    }
    else{
        int randomPos=GameTools::getRandomNum(0, 2);
        GATE_COLOR newColor=gateList.at(randomPos)->getGateColor();
        int newPos= randomPos;
        int specialNum=GameTools::getRandomNum(1, 6);
        if (specialNum==1) {
            newColor=ANY;
            newPos=NONE;
        }
        else if (specialNum==2){
            newColor=pressedColor;
            newPos=NONE;
        }
        if (myDelegate) {
            myDelegate->gatePress(pressedColor, gatePos);
            myDelegate->gateCorrect(newColor, newPos);
        }
    }
}


void GateGroup::addExplosionEffect(GATE_COLOR color,Vec2 point)
{
    return;
    int colorId = (int)color+1;
    if (colorId<1 || colorId>3) {
        return;
    }
    std::string fileName="explosion"+Value(colorId).asString()+".plist";
    ParticleSystemQuad *effect = ParticleSystemQuad::create(fileName);
    auto scene =Director::getInstance()->getRunningScene();
    if (scene) {
        scene->addChild(effect,1000);
    }
    effect->setAutoRemoveOnFinish(true);
    effect->setPosition(point);
}